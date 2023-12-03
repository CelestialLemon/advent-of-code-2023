#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// contains data about a game, how many cubes of each color are present
typedef struct {
    int red;
    int green;
    int blue;
} ColorData;

// read data from file as a vector of strings
std::vector<std::string> get_data() {
    // open file
    std::ifstream input_stream("data.txt");
    std::vector<std::string> data;

    // read data line by line
    std::string file_line;
    while (std::getline(input_stream, file_line)) {
        data.push_back(file_line);
    }

    // close file and return data
    input_stream.close();
    return data;
}

// utility function to split a string into smaller strings at given delimiter (p)
std::vector<std::string> string_split(std::string input, std::string p) {
    // init a container
    std::vector<std::string> tokens;

    // if pattern is present
    while (input.find(p) != std::string::npos) {
        // find index of pattern
        const size_t idx = input.find(p);
        // get substr from [0, idx]
        auto token = input.substr(0, idx);
        // remove the substr from original
        input.erase(0, idx + p.length());
        // push the substr into tokens
        tokens.push_back(token);
    }
    // push whatever is remaining of original string
    tokens.push_back(input);
    // return array
    return tokens;
}

// returns the max number of red, blue and green cubes shown per game
ColorData get_game_data(std::string game_string) {
    // init result
    ColorData game_data = { 0, 0, 0 };
    
    
    // trim the string till the next index of ':'
    game_string = game_string.erase(0, game_string.find(':') + 2);

    // split game data into different shows
    auto shows = string_split(game_string, "; ");
    // std::vector<std::string> color_shows;

    for (auto show : shows) {
        // for each show split into show of individual colors
        // for eg "8 red, 4 blue, 4 green" -> ["8 red", "4 blue", "4 green"]
        auto color_shows = string_split(show, ", ");
        
        // for each color show
        for (auto color_show : color_shows) {
            // split in middle (at space)
            auto color_show_data = string_split(color_show, " ");
            // the first part is the number of cubes shown
            int n_cubes = std::stoi(color_show_data[0]);
            // the second part is the color of the cubes shown
            std::string cubes_color = color_show_data[1];

            // check which color was shown and see if it's the max for this game
            if (cubes_color == "red") {
                game_data.red = std::max(game_data.red, n_cubes);
            }
            else if (cubes_color == "green") {
                game_data.green = std::max(game_data.green, n_cubes);
            }
            else if (cubes_color == "blue") {
                game_data.blue = std::max(game_data.blue, n_cubes);
            }
        }
    }
    // return data
    return game_data;
}

void part1() {
    // set max cubes available
    const int max_red = 12, max_green = 13, max_blue = 14;
    // read data from file
    auto data = get_data();
    // sum of game possible (result)
    int sum = 0;

    for (int i = 0; i < data.size(); i++) {
        // for each game, get max red, blue and green
        ColorData game_data = get_game_data(data[i]);

        // if the any max of the game exceeds max available game is not possible
        if (game_data.red > max_red) {
            // game cannot exist
            std::cout << "Game " << i + 1 << " not possible because red: " << game_data.red << std::endl;
        }
        else if (game_data.green > max_green) {
            // game cannot exist
            std::cout << "Game " << i + 1 << " not possible because green: " << game_data.green << std::endl;
        }
        else if (game_data.blue > max_blue) {
            // game cannot exist
            std::cout << "Game " << i + 1 << " not possible because blue: " << game_data.blue << std::endl;
        } 
        else {
            // game possible
            // std::cout << "Game " << i + 1 << " is possible" << std::endl;
            // add game index to sum
            sum += i + 1;
        }
    }

    // print result
    std::cout << "Sum: " << sum << std::endl;
}

void part2() {
    // get input data
    auto data = get_data();
    // sum of mul (result)
    int sum = 0;

    for (int i = 0; i < data.size(); i++) {
        // get max red, blue, green cubes shown at once in the game
        ColorData game_data = get_game_data(data[i]);

        // find mul
        const int mul = game_data.red * game_data.blue * game_data.green;
        // add to result
        sum += mul;
    }

    // print result
    std::cout << "Sum of mul is : " << sum << std::endl;
}

int main() {
    part1();
    // part2();
}