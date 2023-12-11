#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_set>

typedef struct {
    int x;
    int y;
} Position2D;

// read data.txt as a matrix of chars
std::vector<std::vector<char>> get_data() {
    // open file
    std::ifstream input_stream("data.txt");
    // declare container for data
    std::vector<std::vector<char>> data;
    std::string line;
    // read file line-by-line
    while (std::getline(input_stream, line)) {
        // convert string to vector<char>
        std::vector<char> line_vector(line.begin(), line.end());
        // add vector to matrix
        data.push_back(line_vector);
    }
    // return data
    return data;
}

void print_universe(const std::vector<std::vector<char>>& uv) {
    for (auto& row: uv) {
        for (char c : row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

void expand_universe(std::vector<std::vector<char>>& uv) {
    // loop through rows
    for (int y = 0; y < uv.size(); y++) {
        bool is_row_empty = true;
        for (int x = 0; x < uv[y].size(); x++) {
            if (uv[y][x] != '.') is_row_empty = false;
        }

        if (is_row_empty) {
            std::vector<char> empty_row(uv[y].size(), '.');
            uv.insert(uv.begin() + y, empty_row);
            // skip next row
            y++;
        }
    }

    for (int x = 0; x < uv[0].size(); x++) {
        bool is_column_empty = true;
        for (int y = 0; y < uv.size(); y++) {
            if (uv[y][x] != '.') is_column_empty = false;
        }

        if (is_column_empty) {
            for (int y = 0; y < uv.size(); y++) {
                uv[y].insert(uv[y].begin() + x, '.');
            }
            x++;
        }
    }

}

std::vector<Position2D> find_all_galaxies(const std::vector<std::vector<char>>& uv) {
    std::vector<Position2D> galaxies;

    for (int y = 0; y < uv.size(); y++) {
        for (int x = 0; x < uv[0].size(); x++) {
            if (uv[y][x] == '#') {
                galaxies.push_back({x, y});
            }
        }
    }

    return galaxies; 
}

int manhattan_distance (Position2D a, Position2D b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int find_sum_of_all_distances(const std::vector<Position2D>& galaxies) {
    int total_sum = 0;
    for (int i = 0; i < galaxies.size() - 1; i++) {
        for (int j = i + 1; j < galaxies.size(); j++) {
            total_sum += manhattan_distance(galaxies[i], galaxies[j]);
        }
    }
    return total_sum;
}

void part1(std::vector<std::vector<char>>& uv) {
    expand_universe(uv);
    auto galaxies = find_all_galaxies(uv);
    std::cout << find_sum_of_all_distances(galaxies);
}

bool is_column_empty(const std::vector<std::vector<char>>& uv, Position2D p) {
    for (int y = 0; y < uv.size(); y++) {
        if (uv[y][p.x] != '.') return false;
    }
    return true;
}

bool is_row_empty(const std::vector<std::vector<char>>& uv, Position2D p) {
    for (int x = 0; x < uv[0].size(); x++) {
        if (uv[p.y][x] != '.') return false;
    }
    return true;
}

void part2(std::vector<std::vector<char>>& uv) {
    auto galaxies = find_all_galaxies(uv);
    
    size_t total_sum = 0;
    for (int i = 0; i < galaxies.size() - 1; i++) {
        for (int j = i + 1; j < galaxies.size(); j++) {
            Position2D ga = galaxies[i], gb = galaxies[j];
            int distance = 0;
            // travel rows
            while (ga.x != gb.x) {
                if(is_column_empty(uv, ga)) {
                    distance += 1e6;
                }
                else {
                    distance += 1;
                }
                
                if (ga.x < gb.x) ga.x++;
                else if (ga.x > gb.x) ga.x--;
            }

            while (ga.y != gb.y) {
                if(is_row_empty(uv, ga)) {
                    distance += 1e6;
                }
                else {
                    distance += 1;
                }
                
                if (ga.y < gb.y) ga.y++;
                else if (ga.y > gb.y) ga.y--;
            }

            total_sum += distance;
        }
    }

    std::cout << total_sum;
}

int main() {
    auto uv = get_data();
    // print_univers(uv);
    part2(uv);
    return 0;
}