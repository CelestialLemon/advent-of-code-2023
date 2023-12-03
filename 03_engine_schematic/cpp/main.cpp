#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_set>

typedef struct {
    int x;
    int y;
} Index2D;

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

// starts parsing for a number at given index2d and returns parsed number
// also returns the x-cord of index where parsing stopped
std::pair<int, int> parse_int(Index2D i, const std::vector<std::vector<char>>& matrix) {
    int n = 0;
    while (matrix[i.y][i.x] >= '0' && matrix[i.y][i.x] <= '9') {
        const int digit = matrix[i.y][i.x] - 48;
        n = n * 10 + digit;
        i.x++;

        if (i.x >= matrix[0].size()) break;
    }
    return { n, i.x };
}

// gets all the valid adjacent tiles to a given tile (tile means index)
std::vector<Index2D> get_adjacent_tiles(Index2D i, const std::vector<std::vector<char>>& matrix) {
    // declare lower bound and upper bound for the data
    const int lb = 0, ub = matrix.size();
    // declare container for storing valid adjacent tiles
    std::vector<Index2D> adjacent_tiles;

    // go from { -1, -1 } + index to { 1, 1 } + index to get all adjacent tiles
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            // when { 0, 0 } + index ignore tile
            if (x == 0 && y == 0) continue;

            // calculate adjacent tile's x and y
            const int ax = i.x + x;
            const int ay = i.y + y;

            // check if x and y are valid by comapring with bounds
            if (ax >= lb && ax < ub && ay >= lb && ay < ub) {
                // add index to container if valid
                Index2D adjacent_tile = { ax, ay };
                adjacent_tiles.push_back(adjacent_tile);
            }
        }
    }

    return adjacent_tiles;
}

void part1() {
    auto matrix = get_data();
    int sum = 0;
    
    // iterate over all the data one tile at a time
    for (int y = 0; y < matrix.size(); y++) {
        for (int x = 0; x < matrix[y].size(); x++) {
            // current element
            char e = matrix[y][x];

            // if element is a number, parse the number beginning at current index
            if (e >= '0' && e <= '9') {
                // is part of engine
                bool is_part = false;
                // get the parsed number and x-cord where parsing stopped
                auto parse_data = parse_int({ x, y }, matrix);
                // n is parsed number
                const int n = parse_data.first;
                // new_x is where parsing stopped
                const int new_x = parse_data.second;

                // find all adjacent tiles for give number
                std::vector<Index2D> all_adjacent_tiles;
                // iterate from current x to new_x with same y and find adjacent tiles for those tiles 
                // (as these tiles make up the number)
                for (int it = x; it < new_x; it++) {
                    auto adjacent_tiles = get_adjacent_tiles({ it, y }, matrix);
                    all_adjacent_tiles.insert(all_adjacent_tiles.end(), adjacent_tiles.begin(), adjacent_tiles.end());
                }

                // check all adjacent tiles for symbols
                for (auto adjacent_index : all_adjacent_tiles) {
                    const char le = matrix[adjacent_index.y][adjacent_index.x];

                    // if the adjacent element is not . or a number it's a symbol
                    if (le != '.' && (le < '0' || le > '9')) {
                        // is a symbol
                        is_part = true;
                        break;
                    }
                }

                if (is_part) sum += n;
                x = new_x - 1;
            }
        } 
    }

    std::cout << "Result: " << sum << '\n';
}


// std::vector<Index2D> get_adjacent_tiles2(Index2D i, const std::vector<std::vector<char>>& matrix) {
//     std::vector<Index2D> adjacent_tiles;

//     // go from { -1, -1 } + index to { 1, 1 } + index to get all adjacent tiles
//     for (int y = -1; y <= 1; y++) {
//         for (int x = -1; x <= 1; x++) {
//             if (x == 0 && y == 0) continue;

//             Index2D adjacent_tile = { i.x + x, i.y + y };
//             adjacent_tiles.push_back(adjacent_tile);
//         }
//     }

//     return adjacent_tiles;
// }

int parse_int2 (Index2D i, const std::vector<std::vector<char>>& matrix) {
    // get to the index where the number starts
    while (i.x > 0) {
        char prev_el = matrix[i.y][i.x - 1];
        if (prev_el >= '0' && prev_el <= '9') {
            i.x -= 1;
        }
        else break;
    }

    return parse_int(i, matrix).first;
}


void part2 () {
    auto matrix = get_data();
    int sum = 0;

    for (int y = 0; y < matrix.size(); y++) {
        for (int x = 0; x < matrix[0].size(); x++) {
            const char e = matrix[y][x];

            if (e == '*') {
                auto adjacent_tiles = get_adjacent_tiles({ x, y }, matrix);

                std::unordered_set<int> adjacent_numbers;
                for (auto adjacent_tile : adjacent_tiles) {
                    const char le = matrix[adjacent_tile.y][adjacent_tile.x];

                    if (le >= '0' && le <= '9') {
                        // we have a number adjacent to the star
                        adjacent_numbers.insert(parse_int2({ adjacent_tile.x, adjacent_tile.y }, matrix));
                    }
                }

                if (adjacent_numbers.size() == 2) {
                    int fac = 1;
                    for (auto n : adjacent_numbers) fac *= n;
                    sum += fac;
                }
            }
        }
    }

    std::cout << "Result Part two: " << sum << '\n';
}

int main () {
    // part1();
    part2();
}