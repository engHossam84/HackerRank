/*We have defined our own markup language HRML. In HRML, each element consists of a starting and ending tag, and there are attributes associated with each tag. Only starting tags can have attributes. We can call an attribute by referencing the tag, followed by a tilde, '~' and the name of the attribute. The tags may also be nested.

The opening tags follow the format:

<tag-name attribute1-name = "value1" attribute2-name = "value2" ...>

The closing tags follow the format:

</tag-name>

For example:

<tag1 value = "HelloWorld">
<tag2 name = "Name1">
</tag2>
</tag1>
The attributes are referenced as:

tag1~value  
tag1.tag2~name
You are given the source code in HRML format consisting of N lines. You have to answer Q queries. Each query asks you to print the value of the attribute specified. Print "Not Found!" if there isn't any such attribute.

Input Format

The first line consists of two space separated integers,  and .  specifies the number of lines in the HRML source program.  specifies the number of queries.

The following  lines consist of either an opening tag with zero or more attributes or a closing tag.There is a space after the tag-name, attribute-name, '=' and value.There is no space after the last value. If there are no attributes there is no space after tag name.

 queries follow. Each query consists of string that references an attribute in the source program.More formally, each query is of the form ~ where  and  are valid tags in the input.

Constraints

Each line in the source program contains, at max,  characters.
Every reference to the attributes in the  queries contains at max  characters.
All tag names are unique and the HRML source program is logically correct.
A tag can have no attributes as well.
Output Format

Print the value of the attribute for each query. Print "Not Found!" without quotes if there is no such attribute in the source program.

Sample Input

4 3
<tag1 value = "HelloWorld">
<tag2 name = "Name1">
</tag2>
</tag1>
tag1.tag2~name
tag1~name
tag1~value
Sample Output

Name1
Not Found!
HelloWorld

*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <sstream>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    unordered_map<string, string> map;

    int N, Q;
    string parentTag = "";
    cin >> N;
    cin    >> Q;
    string line;
    getline(cin, line);
    string concat;
    bool lastAttribute = false;
    for (size_t i = 0; i < N; i++)
    {
        getline(cin, line);
        string tag, attr;
        //cout << "Line = " << line << endl;
        stringstream ss(line);
        string key, value;
        ss >> tag;
        if (tag[1] != '/')
        {

            if (tag.at(tag.size() - 1) != '>')  //empty tag
            {
                if (parentTag.empty())
                    tag = tag.substr(1);
                else
                    tag = parentTag + "." + tag.substr(1);
                parentTag = tag;

                
                do{
                    ss >> attr;
                    ss >> value;
                    ss >> value;
                    while (value.at(value.size() - 1) != '>' && value.at(value.size() - 1) != '"')
                    {
                        ss >> concat;
                        value  = value +" "+ concat;
                    }
                    if (value.at(value.size() - 1) == '>')
                    {
                        value = value.substr(1, value.size() - 3);
                        lastAttribute = true;
                    }
                    else
                        value = value.substr(1, value.size() - 2);
                    key = tag + "~" + attr;
                    if (!key.empty())
                    {
                       // cout << "Key = " << key << endl;
                       // cout << "value = " << value << endl;
                        map[key] = value;
                    }

                } while (lastAttribute == false);
                lastAttribute = false;
                
                
                
            }
            else
            {
                if (parentTag.empty())
                    tag = tag.substr(1, tag.size() - 2);
                else
                    tag = parentTag + "." + tag.substr(1,tag.size() - 2);
                parentTag = tag;

            }
        }
        else
        {
            size_t pos = parentTag.find(tag.substr(2, tag.size() - 3));
            if (pos == 0) // only one tag
                parentTag.erase(pos);
            else
                parentTag.erase(--pos);
        }

        

    }

    for (size_t i = 0; i < Q; i++)
    {
        string line;
        getline(cin, line);
        auto record = map.find(line);
        if (record != map.end())
            cout << record->second << endl;
        else
            cout << "Not Found!" << endl;

    }
            


    return 0;
}
