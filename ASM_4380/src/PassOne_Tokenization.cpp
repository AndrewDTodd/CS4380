#include "../include/PassOne_Tokenization.h"

#include <memory>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <shared_mutex>
#include <unordered_map>
#include <stdexcept>
#include <regex>
#include <utility>
#include <iostream>

std::pair<std::vector<std::string>, std::string> PassOne_Tokenization::TokenizeLine(const std::string& line) const
{
    std::vector<std::string> tokens;
    std::string comment;
    std::string withoutComment;

    size_t semicolonPos = line.find_first_of(';');
    while (semicolonPos != std::string::npos)
    {
        size_t precedingQuotePos = line.rfind('\'', semicolonPos);
        size_t followingQuotePos = line.find('\'', semicolonPos);

        if (precedingQuotePos == std::string::npos || followingQuotePos == std::string::npos)
        {
            // Semicolon is not within single quotes
            comment = line.substr(semicolonPos);
            //Extract the stuff before the comment
            withoutComment = line.substr(0, semicolonPos);
            break;
        }

        semicolonPos = line.find_first_of(';', semicolonPos + 1);
    }

    if (!withoutComment.empty())
    {
        //Process withoutComment to extract the tokens
        //Old regex string (\.\w+)|('.')|('\\[tnr]')|(\#\d+)
        std::regex rgx(R"delim((\.?\w+(?=\,*\s+|$))|('.'(?=\s+|$))|('\\[tnr]'(?=\s+|$))|(\#\d+(?=\s+|$))|(".*?"(?=\s+|$)))delim", std::regex_constants::ECMAScript);
            std::sregex_iterator iter(withoutComment.begin(), withoutComment.end(), rgx);
            std::sregex_iterator end;

            for (; iter != end; ++iter)
            {
                std::smatch match = *iter;
                tokens.push_back(match.str());
            }
    }

    return std::make_pair(tokens, comment);
}

void PassOne_Tokenization::AddLabel(const std::string& label, ASMFramework::Workpiece* const& workpiece) const
{
    workpiece->_symbolTable.emplace(label, 0);
}

void PassOne_Tokenization::HandleDirective(const size_t& lineNum, std::string&& label, const std::string& directive, const std::vector<std::string>& arguments, std::string&& comment, 
    ASMFramework::Workpiece* const& workpiece, const ASMFramework::LanguageDefinition* const& langDef) const
{
    workpiece->_dataSegmentItems.emplace_back(label, ASMFramework::DataSegmentItem{ lineNum, langDef->GetDirective(directive), arguments, comment });
}

void PassOne_Tokenization::HandleInstruction(const size_t& lineNum, const std::string& instruction, const std::vector<std::string>& arguments, std::string&& comment,
    std::vector<ASMFramework::CodeSegmentItem>* const& segment, const ASMFramework::LanguageDefinition* const& langDef) const
{
    segment->emplace_back(ASMFramework::CodeSegmentItem{ lineNum, langDef->GetInstruction(instruction), arguments, comment });
}

void PassOne_Tokenization::HandleCodeSegmentItem(const std::string& label, const std::vector<ASMFramework::CodeSegmentItem>& segment,
    ASMFramework::Workpiece* const& workpiece) const
{
    workpiece->_codeSegmentItems.emplace_back(label, segment);
}

void PassOne_Tokenization::ProcessDataSegment(size_t& lineNum, ASMFramework::Workpiece* const& workpiece, std::ifstream& fileStream, const ASMFramework::LanguageDefinition* const& langDef) const
{
    std::string line;
    while (std::getline(fileStream, line))
    {
        lineNum++;
        auto tokenAndComment = TokenizeLine(line);
        auto& tokens = tokenAndComment.first;
        auto& comment = tokenAndComment.second;

        if (!tokens.empty())
        {
            std::string firstToken = tokens[0];
            tokens.erase(tokens.begin());

            if (langDef->ContainsKeyword(firstToken))
                throw std::runtime_error("First token at line number" + std::to_string(lineNum) + " is a reserved keyword \"" + firstToken + 
                    "\" and is not valid in this context. Expected a Label, Directive, or an Instruction mnemonic");

            if (langDef->ContainsInstruction(firstToken))
            {
                lineNum--;
                fileStream.seekg(std::ios_base::beg);
                for (int i = 0; i < lineNum; i++)
                {
                    std::getline(fileStream, line);
                }
                break;
            }

            if (!langDef->ContainsDirective(firstToken))
            {
                //Assume its a label at this point
                //verify format
                std::regex labelFormat("^[a-zA-Z][a-zA-Z0-9_]*$");
                if (!std::regex_match(firstToken, labelFormat))
                    throw std::runtime_error("Invalid label format - \"" + firstToken + "\" - at line number" + std::to_string(lineNum) +
                        "\nLabels must start with alphabetical symbol (a-zA-Z) and then contain only alphabetical (a-zA-Z) or numeric (0-9) or underscore (_) symbols");

                //check to see if label is duplicate
                if (workpiece->_symbolTable.contains(firstToken))
                    throw std::runtime_error("Duplicate label found on line number" + std::to_string(lineNum) + ". \"" + firstToken +
                        "\" is already in the symbol table");

                std::string secondToken = tokens[0];
                tokens.erase(tokens.begin());

                if (langDef->ContainsKeyword(secondToken))
                    throw std::runtime_error("Second token at line number" + std::to_string(lineNum) + " is a reserved keyword \"" + secondToken + 
                        "\" and is not valid in this context. Expected a Directive, or an Instruction mnemonic");

                if (langDef->ContainsInstruction(secondToken))
                {
                    lineNum--;
                    fileStream.seekg(std::ios_base::beg);
                    for (int i = 0; i < lineNum; i++)
                    {
                        std::getline(fileStream, line);
                    }
                    break;
                }

                AddLabel(firstToken, workpiece);

                //At this point we know the second token is a directive
                HandleDirective(lineNum, std::move(firstToken), secondToken, tokens, std::move(comment), workpiece, langDef);
            }
            else
            {
                //firstToken is a directive
                HandleDirective(lineNum, "", firstToken, tokens, std::move(comment), workpiece, langDef);
            }
        }
    }
}

void PassOne_Tokenization::ProcessCodeSegment(size_t& lineNum, ASMFramework::Workpiece* const& workpiece, std::ifstream& fileStream, const ASMFramework::LanguageDefinition* const& langDef) const
{
    std::string line;
    std::vector<ASMFramework::CodeSegmentItem> segment;
    std::string segmentLabel = "";
    while (std::getline(fileStream, line))
    {
        lineNum++;
        auto tokenAndComment = TokenizeLine(line);
        auto& tokens = tokenAndComment.first;
        auto& comment = tokenAndComment.second;

        if (!tokens.empty())
        {
            std::string firstToken = tokens[0];
            tokens.erase(tokens.begin());

            if (langDef->ContainsKeyword(firstToken))
                throw std::runtime_error("First token at line number" + std::to_string(lineNum) + " is a reserved keyword \"" + firstToken + 
                    "\" and is not valid in this context. Expected a Label, or an Instruction mnemonic");

            if (langDef->ContainsDirective(firstToken))
                throw std::runtime_error("First token at line number" + std::to_string(lineNum) + " is a Directive mnemonic \"" + firstToken + 
                    "\" and is not valid outside of the data segment. Expected a Label, or an Instruction mnemonic");

            if (!langDef->ContainsInstruction(firstToken))
            {
                //Assume its a label at this point
                //verify format
                std::regex labelFormat("^[a-zA-Z][a-zA-Z0-9_]*$");
                if (!std::regex_match(firstToken, labelFormat))
                    throw std::runtime_error("Invalid label format - \"" + firstToken + "\" - at line number" + std::to_string(lineNum) +
                        "\nLabels must start with alphabetical symbol (a-zA-Z) and then contain only alphabetical (a-zA-Z) or numeric (0-9) or underscore (_) symbols");

                //check to see if label is duplicate
                if (workpiece->_symbolTable.contains(firstToken))
                    throw std::runtime_error("Duplicate label found on line number" + std::to_string(lineNum) + ". \"" + firstToken +
                        "\" is already in the symbol table");

                std::string secondToken = tokens[0];
                tokens.erase(tokens.begin());

                if (langDef->ContainsKeyword(secondToken))
                    throw std::runtime_error("Second token at line number" + std::to_string(lineNum) + " is a reserved keyword \"" + secondToken + "\" and is not valid in this context. Expected an Instruction mnemonic");

                if (langDef->ContainsDirective(secondToken))
                    throw std::runtime_error("Second token at line number" + std::to_string(lineNum) + " is a Directive mnemonic \"" + secondToken +
                        "\" and is not valid outside of the data segment. Expected a Label, or an Instruction mnemonic");

                AddLabel(firstToken, workpiece);

                //As we have a new label we are beggining a new code segment. Save the previouse one
                if (!segment.empty())
                    HandleCodeSegmentItem(segmentLabel, segment, workpiece);

                segmentLabel = firstToken;

                //clear the segment buffer
                segment.clear();

                //At this point we know the second token is  the first instruction of this new code segment
                HandleInstruction(lineNum, secondToken, tokens, std::move(comment), &segment, langDef);
            }
            else
            {
                //firstToken is an instruction. add it to the segment buffer
                HandleInstruction(lineNum, firstToken, tokens, std::move(comment), &segment, langDef);
            }
        }
    }

    //Save the last segment buffer before exiting
    if (!segment.empty())
        HandleCodeSegmentItem(segmentLabel, segment, workpiece);
}

void PassOne_Tokenization::Execute(ASMFramework::Workpiece* const& workpiece, const std::filesystem::path& filePath, const ASMFramework::LanguageDefinition* const& langDef) const
{
    size_t lineNumber = 0;

    std::ifstream fileStream(filePath.string());

    if (!fileStream.is_open())
        throw std::runtime_error("Unable to open file at path: " + filePath.string());

    //Data segment, if there is one, is first. Will break when code segment is reached and set the fileStream to that line
    ProcessDataSegment(lineNumber, workpiece, fileStream, langDef);

    //Process the code segment after the data segment
    ProcessCodeSegment(lineNumber, workpiece, fileStream, langDef);

    fileStream.close();

    GREEN_TERMINAL
        std::cout << " >>> Tokenization Complete" << std::endl;
    RESET_TERMINAL
}