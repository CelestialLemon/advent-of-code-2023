#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

typedef struct {
    int red;
    int green;
    int blue;
} ColorData;

std::vector<std::string> get_data() {
    std::ifstream input_stream("data.txt");
    std::vector<std::string> data;

    std::string file_line;
    while (std::getline(input_stream, file_line)) {
        data.push_back(file_line);
    }

    input_stream.close();
    return data;
}

std::vector<std::string> string_split(std::string input, std::string p) {
    std::vector<std::string> tokens;

    while (input.find(p) != std::string::npos) {
        const size_t idx = input.find(p);
        auto token = input.substr(0, idx);
        input.erase(0, idx + p.length());
        tokens.push_back(token);
    }
    tokens.push_back(input);
    return tokens;
}

ColorData get_game_data(std::string game_string) {
    ColorData game_data = { 0, 0, 0 };
    
    // trim the string till the next index of ':'
    game_string = game_string.erase(0, game_string.find(':') + 2);

    auto shows = string_split(game_string, "; ");
    // std::vector<std::string> color_shows;

    for (auto show : shows) {
        auto color_shows = string_split(show, ", ");
        
        for (auto color_show : color_shows) {
            auto color_show_data = string_split(color_show, " ");
            int n_cubes = std::stoi(color_show_data[0]);
            std::string cubes_color = color_show_data[1];

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
    
    return game_data;
}


int main() {
    const int max_red = 12, max_green = 13, max_blue = 14;
    auto data = get_data();
    int sum = 0;

    for (int i = 0; i < data.size(); i++) {
        ColorData game_data = get_game_data(data[i]);

        if (game_data.red > max_red || game_data.green > max_green || game_data.blue > max_blue) {
            // game cannot exist
        } 
        else {
            std::cout << "Game " << i + 1 << " is possible" << std::endl;
            sum += i + 1;
        }
    }

    std::cout << "Sum: " << sum << std::endl;
}