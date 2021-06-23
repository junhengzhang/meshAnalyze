#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iosfwd>
#include "panel.cpp"

using std::istringstream;

// for string delimiter
std::vector<std::string> split (std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        if (token.size()>0)
            res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

int main ()
{
    //open file
    std::ifstream file ("../hamburg_test_case.pan");
    //std::ifstream file ("../hull_198.pan");
    //get first line because it contains amount of nodes
    std::string firstLine;
    getline(file, firstLine);

    //convert the information info integer
    int allNodes = std::stoi(firstLine);

    //put every node and panel in an list
    std::vector<std::string> nodeList;
    std::vector<std::string> panelList;

    std::string line;
    //loop throw lines
    int i = 0;
    while(file) {
         std::getline(file, line);
         //put nodes in node list
         if (i<allNodes)
             nodeList.emplace_back(line);
         //line where numbers of panels stated -> bypass
         else if (i==allNodes) {}
         //put all panels in list
         else if (i>allNodes)
             panelList.emplace_back(line);

         i=i+1;
     }
    //file.close();

    //generate a array of point objects
    std::string delimiter = " ";

    //std::string word;

    //get the nodes into a array of point objects
    std::vector<Point> point;
    int index = 1;
    for (const std::string& everyLine : nodeList ){
        //split the words in nodeLine into chunks and put them into a temp vector
        std::string token = everyLine.substr(0, everyLine.find(delimiter));
        std::vector<std::string> everyString = split (everyLine, delimiter);

        point.emplace_back(index, std::stof(everyString[0]), std::stof(everyString[1]), std::stof(everyString[2]));
        index=index+1;
    }

    //get the panel into a array of panel objects
    std::vector<Panel> panel;
    for (const std::string& everyLine : panelList ){
        //split the words in nodeLine into chunks and put them into a temp vector
        std::string token = everyLine.substr(0, everyLine.find(delimiter));
        std::vector<std::string> everyString = split (everyLine, delimiter);

        //tri
        if(everyString[0]=="3")
            panel.emplace_back(
                    std::stoi( everyString[0]),
                    point[std::stoi(everyString[1])-1],
                    point[std::stoi(everyString[2])-1],
                    point[std::stoi(everyString[3])-1]
                               );
        //quad
        if(everyString[0]=="4")
            panel.emplace_back(
                    std::stoi( everyString[0]),
                    point[std::stoi(everyString[1])-1],
                    point[std::stoi(everyString[2])-1],
                    point[std::stoi(everyString[3])-1],
                    point[std::stoi(everyString[4])-1]
            );
    }

    for(i=0; i<point.size(); i++)
        std::cout << point[i].idx << ": " << point[i].x << " " << point[i].y << " " << point[i].z << std::endl;
    for(i=0; i<panel.size(); i++)
        std::cout << i+1 << ": " << panel[i].p1.idx << " " << panel[i].p2.idx << " " << panel[i].p3.idx << " " << panel[i].p4.idx << " : max Length: " << panel[i].maxLengthEdge() << std::endl;
}

