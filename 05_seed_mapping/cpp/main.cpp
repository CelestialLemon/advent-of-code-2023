#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>

struct MappingInfo {
    size_t s;
    size_t d;
    size_t l;
};

std::vector<std::vector<MappingInfo>> all_mappings;

std::vector<std::string> splitString(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(s);
    std::string token;
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> readData() {
    std::ifstream file("data.txt");
    std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::vector<std::string> data2 = splitString(data, '`');

    for (size_t it = 9; it <= 45; it += 6) {
        const std::string& mappingData = data2[it];
        std::vector<MappingInfo> mappings;
        std::vector<std::string> lines = splitString(mappingData, '\n');

        for (const std::string& mappingLine : lines) {
            std::vector<std::string> tokens = splitString(mappingLine, ' ');
            size_t d = std::stoull(tokens[0]);
            size_t s = std::stoull(tokens[1]);
            size_t l = std::stoull(tokens[2]);
            MappingInfo mi = { d, s, l };
            mappings.push_back(mi);
        }

        all_mappings.push_back(mappings);
    }

    return data2;
}

size_t findMapping(size_t n, const std::vector<MappingInfo>& map) {
    for (size_t i = 0; i < map.size(); i++) {
        const MappingInfo& mi = map[i];
        size_t sourceLowerBound = mi.s, sourceUpperBound = mi.s + mi.l - 1;
        if (n >= sourceLowerBound && n <= sourceUpperBound) {
            // mapping found
            return n + (mi.d - mi.s);
        }
    }
    return n;
}

void part1(std::vector<std::string>& data2) {
    const std::vector<std::string>& seedsString = splitString(data2[3], ' ');
    size_t minLocation = std::numeric_limits<size_t>::max();

    for (const std::string& seedString : seedsString) {
        size_t seed = std::stoull(seedString);
        size_t currentMapValue = seed;

        for (const std::vector<MappingInfo>& mapping : all_mappings) {
            currentMapValue = findMapping(currentMapValue, mapping);
        }

        minLocation = std::min(minLocation, currentMapValue);
    }

    std::cout << minLocation << std::endl;
}

void part2(std::vector<std::string>& data2) {
    const std::vector<std::string>& seedsString = splitString(data2[3], ' ');
    size_t minLocation = std::numeric_limits<size_t>::max();

    for (size_t i = 0; i < seedsString.size(); i += 2) {
        size_t s = std::stoull(seedsString[i]);
        size_t l = std::stoull(seedsString[i + 1]);

        for (size_t si = s; si < s + l; si++) {
            size_t currentMapValue = si;

            for (const std::vector<MappingInfo>& mapping : all_mappings) {
                currentMapValue = findMapping(currentMapValue, mapping);
            }

            minLocation = std::min(minLocation, currentMapValue);
        }

        // std::cout << "index " << i << " done" << std::endl;
    }

    std::cout << minLocation << std::endl;
}

int main() {
    auto data2 = readData();
    
    // for (size_t i = 0; i < data2.size(); i++) {
    //     const auto token = data2[i];
    //     std::cout << "Index: " << i << " `" << token << '`' << std::endl;
    // }
    // part1(data2);
    part2(data2);

    return 0;
}
