import { readFileSync } from 'node:fs';

const part1 = () => {
    let data = readFileSync('data.txt');

const lines: string[] = data.toString().split('\n');

let sum = 0;

lines.forEach(line => {
    line = line.substring(10, line.length);
    
    const [winning_numbers_s, our_numbers_s] = line.split('| ');

    // console.log(winning_numbers_s.split(' '));

    const wn: number[] = winning_numbers_s.split(' ').filter(ns => ns != '').map(number_string => parseInt(number_string));
    const on: number[] = our_numbers_s.split(' ').filter(ns => ns != '').map(number_string => parseInt(number_string));

    let card_value = 0;

    on.forEach(our_number => {
        const idx = wn.indexOf(our_number);

        if (idx == -1 ) {
            // element not found
        }
        else {
            // element found
            card_value = card_value == 0 ? 1 : card_value * 2;
        }
    })

    sum += card_value;
})

    console.log(`Total value: ${sum}`);
}

const part2 = () => {
    const games = readFileSync('data.txt').toString().split('\n');
    const n_copies = Array(games.length).fill(1);
    games.forEach((game, index) => {
        game = game.substring(10);
        const [winning_numbers_s, our_numbers_s] = game.split('| ');

        const wn: number[] = winning_numbers_s.split(' ').filter(ns => ns != '').map(number_string => parseInt(number_string));
        const on: number[] = our_numbers_s.split(' ').filter(ns => ns != '').map(number_string => parseInt(number_string));

        let matches = 0;
        on.forEach(our_number => {
            if (wn.indexOf(our_number) != -1) {
                // element found
                matches++;
            }
        })

        for (let it = index + 1; it <= index + matches; it++) {
            n_copies[it] += n_copies[index];
        }
    })

    let sum = 0;
    n_copies.forEach(copy => sum += copy);
    console.log(`Result: ${sum}`);
}

part2();