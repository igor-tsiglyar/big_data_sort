#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <fstream>
#include <regex>


std::shared_ptr<std::map<int, std::string>> read_records(const std::string & filepath) {
    std::shared_ptr<std::map<int, std::string>> result = std::make_shared<std::map<int, std::string>>();

    std::regex record_re("<%%%%><(\\d+)><([a-z]+)><\\$\\$\\$>");
    std::smatch record_match_results;

    std::ifstream ifs(filepath);
    std::shared_ptr<std::string> records = std::make_shared<std::string>(
            std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    std::string::const_iterator search_start(records->cbegin());

    while (std::regex_search(search_start, records->cend(), record_match_results, record_re)) {
        (*result)[std::stoi(record_match_results[1].str())] = record_match_results[2].str();
        search_start += record_match_results.position() + record_match_results.length();
    }

    return result;
};


void merge(std::vector<int> & keys, std::vector<int> & temp, int start, int centre, int end)
{
    int tmp_pos = 0;
    int num_pos = start;
    int final_pos = start;

    while(num_pos <= centre) {
        temp[tmp_pos++] = keys[num_pos++];
    }

    tmp_pos = 0;

    while(final_pos < num_pos && num_pos <= end)
    {
        if(temp[tmp_pos] <= keys[num_pos]) {
            keys[final_pos++] = temp[tmp_pos++];
        } else {
            keys[final_pos++] = keys[num_pos++];
        }
    }

    while(final_pos < num_pos) {
        keys[final_pos++] = temp[tmp_pos++];
    }
}


void sort(std::vector<int> & keys, std::vector<int> & temp, int start, int end)
{
    if(start < end) {
        int centre = (start + end) / 2;
        sort(keys, temp, start, centre);
        sort(keys, temp, centre + 1, end);
        merge(keys, temp, start, centre, end);
    }
}


std::shared_ptr<std::vector<int>> get_write_order(const std::map<int, std::string> & records) {
    std::shared_ptr<std::vector<int>> keys = std::make_shared<std::vector<int>>();
    std::transform(records.cbegin(), records.cend(), std::back_inserter(*keys),
                   [](const std::map<int, std::string>::value_type & pair) { return pair.first; });
    std::shared_ptr<std::vector<int>> temp = std::make_shared<std::vector<int>>(keys->size());

    sort(*keys, *temp, 0, keys->size() - 1);

    return keys;
};


void write_records(const std::map<int, std::string> & records, const std::string & filepath) {
    std::ofstream ofs(filepath);

    std::shared_ptr<std::vector<int>> ordered_keys = get_write_order(records);

    for (int key : *ordered_keys) {
        ofs << "<%%%><" << key << "><" << records.at(key) << "><$$$>";
    }
};


int main(int argc, char *argv[]) {
    std::string filepath = argv[1];
    std::shared_ptr<std::map<int, std::string>> records = read_records(argv[1]);
    write_records(*records, filepath + "_sorted");

    return 0;
}