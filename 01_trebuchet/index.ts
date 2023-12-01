const fs = require('fs');

const data: string = fs.readFileSync('input.txt', 'utf-8');

const lines: string[] = data.split('\n');

let sum = 0;
const word_numbers = [
    'one',
    'two',
    'three',
    'four',
    'five',
    'six',
    'seven',
    'eight',
    'nine'
];

const word_number_mapping = {
    'one': 1,
    'two': 2,
    'three': 3,
    'four': 4,
    'five': 5, 
    'six': 6,
    'seven': 7,
    'eight': 8,
    'nine': 9
};

const compare_string_from_current_position = (line: string, index: number, pattern: string): boolean => {
    if (pattern.length == 0) return false;
    let i = index;
    for (; i - index < pattern.length && i < line.length; i++) {
        if (line[i] != pattern[i - index]) {
            return false;
        }
    }

    if (i - index < pattern.length) return false;
    
    return true;
}

const find_left_number = (line: string): number => {
    for (let i = 0; i < line.length; i++) {
        if (line[i] >= '0' && line[i] <= '9') {
            const result =  parseInt(line[i]);
            if (result != undefined) return result;
        }
        else {
            for (let j = 0; j < word_numbers.length; j++) {
                const word_number = word_numbers[j];
                if(compare_string_from_current_position(line, i, word_number)) {
                    // word hit
                    return word_number_mapping[word_number];
                }
            }
        }
    }
    return 0;
}

const find_right_number = (line: string): number => {
    for (let i = line.length - 1; i >= 0; i--) {
        if (line[i] >= '0' && line[i] <= '9') {
            const result =  parseInt(line[i]);
            if (result != undefined) return result;
        }
        else {
            for (let j = 0; j < word_numbers.length; j++) {
                const word_number = word_numbers[j];
                if(compare_string_from_current_position(line, i, word_number)) {
                    // word hit
                    console.log(`hit between word and line ${word_number} ${line}`);
                    return word_number_mapping[word_number];
                }
            }
        }
    }
    return 0;
}

lines.forEach((line: string) => {
    let left_number = find_left_number(line);
    let right_number = find_right_number(line);

    

    sum += left_number * 10 + right_number;
})

console.log(sum);

// console.log(find_left_number("two1nine"));
// console.log(find_right_number("two1nine"));