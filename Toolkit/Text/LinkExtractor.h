/*
 * TODO:
 * 1) CHECK HOW IT WORKS WITH NON-ASCII CHARACTERS: WE MAY NEED TO USE A wstring AS INPUT
 */

#pragma once

#include <string>

struct ExtractedLink
{
    int offset;
    int length;
    std::string url;
    
    ExtractedLink(int offset, int length, std::string url) : offset(offset), length(length), url(url) {}
};

class LinkExtractor
{
public:
    static std::pair<std::vector<ExtractedLink>, std::string> extract(const std::string &input)
    {
        std::vector<ExtractedLink> links;
        std::string output;
        
        size_t pos = 0;
        
        while (true)
        {
            int pos1 = input.find("<a href=\"", pos);
            
            if (pos1 != std::string::npos)
            {
                int pos2 = pos1 + 9;
                int pos3 = input.find("\">", pos2);
                
                int pos4 = pos3 + 2;
                int pos5 = input.find("</a>", pos4);

                output.append(input, pos, pos1 - pos);
                links.push_back(ExtractedLink(output.size(),pos5 - pos4, input.substr(pos2, pos3 - pos2)));
                output.append(input, pos4, pos5 - pos4);

                pos = pos5 + 4;
            }
            else
            {
                output.append(input.begin() + pos, input.end());
                break;
            }
        }
        
        return make_pair(links, output);
    }
};
