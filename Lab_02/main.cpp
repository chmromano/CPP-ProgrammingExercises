#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string find_field(const string &xml, string tag_name);

int main() {
    string page, line, location, temperature;
    ifstream inputFile("weather.xml");

    while (getline(inputFile, line)) {
        page.append(line);
        line.erase();
    }

    location = find_field(page, "location");
    temperature = find_field(page, "temp_c");

    cout << "Location: " << location << endl;
    cout << "Temperature: " << temperature << endl;

    return 0;
}

string find_field(const string &xml, string tag_name) {
    // Generate start and end tags.
    string start_tag("<" + tag_name + ">"), end_tag("</" + tag_name + ">");

    //Find start and end position of searched item's string.
    int start_pos = xml.find(start_tag) + start_tag.size();
    int end_pos = xml.find(end_tag);

    if (start_pos == string::npos || end_pos == string::npos) {
        return "not found"; // Return this if tag is not found.
    } else {
        return xml.substr(start_pos, end_pos - start_pos); // Return substring if tag is found.
    }
}
