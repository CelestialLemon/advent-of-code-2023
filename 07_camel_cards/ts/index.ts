import { readFileSync } from 'node:fs';

// struct for storing hands with their bids
type Hand = {
    hand: string,
    bid: number
};

// type of hands in increasing order of power
enum HandType {
    HIGH,
    ONE_PAIR,
    TWO_PAIR,
    THREE,
    FULL_HOUSE,
    FOUR,
    FIVE
};

// read data
const data = readFileSync('data.txt', 'utf-8').split('\n');

// declare buffer to store parsed data
const hands: Hand[] = [];

// split each line and read the hand and bid
data.forEach(line => {
    const [hs, bs] = line.split(' ');
    hands.push({ hand: hs, bid: parseInt(bs) }); 
})

const part1 = () => {
    // declare value / power for each card
    const card_values = {
        '2': 2,
        '3': 3,
        '4': 4,
        '5': 5,
        '6': 6,
        '7': 7,
        '8': 8,
        '9': 9,
        'T': 10,
        'J': 11,
        'Q': 12,
        'K': 13,
        'A': 14
    };

    // find type of a hand
    const find_hand_type = (hand: string) : HandType => {
        // map for storing frequencies of different cards, 
        // card is key, its' freq is the value
        const fq: {[key: string]: number} = {};
        // loop over all cards
        for (let i = 0; i < hand.length; i++) {
            const card = hand[i];
            if (fq[card] == undefined) {
                // card does not exist
                // add card to map with freq of 1
                fq[card] = 1;
            }
            else {
                // card exists, increase frequency
                fq[card]++;
            }
        }
        
        // an array of all the frequencies that occur in the hand
        const frequencies: number[] = [];
        // loop through map entries and add frequencies to array
        Object.entries(fq).forEach(entry => {
            frequencies.push(entry[1]);
        });
        // sort the array in decending order so larger frequencies comes first
        frequencies.sort((a, b) => a > b ? -1 : 1);
        
        // decide type of hand depending on the first and second highest freqencies
        if (frequencies[0] == 5) return HandType.FIVE;
        else if (frequencies[0] == 4) return HandType.FOUR;
        else if (frequencies[0] == 3 && frequencies[1] == 2) return HandType.FULL_HOUSE;
        else if(frequencies[0] == 3) return HandType.THREE;
        else if (frequencies[0] == 2 && frequencies[1] == 2) return HandType.TWO_PAIR;
        else if (frequencies[0] == 2) return HandType.ONE_PAIR;
        else return HandType.HIGH;
    }
    
    // sort the hands by their power
    hands.sort((a, b) => {
        const hta = find_hand_type(a.hand);
        const htb = find_hand_type(b.hand);
    
        if (hta != htb) {
            // if hand of a is stronger than b move it to prior position
            if (hta > htb) return -1;
            else return 1;
        }
        else {
            // if the type of hand is same, iterate over cards and 
            // the first card to have a greater value in either hand is the stronger one
            for (let i = 0; i < 5; i++) {
                if(card_values[a.hand[i]] > card_values[b.hand[i]]) return -1;
                else if (card_values[a.hand[i]] < card_values[b.hand[i]]) return 1;
                else continue;
            }
            return 0;
        }
    });
    
    let sum = 0;
    // iterate over arrays, the first hand is the strongest so it's rank is maximum and the last hand is 1
    hands.forEach((hand, index) => {
        const rank = hands.length - index;
        sum += rank * hand.bid;
        // console.log(`hand: ${hand.hand}, bid: ${hand.bid}, rank: ${rank}, value: ${rank * hand.bid}`);
    })
    
    console.log(sum);
}

const part2 = () => {

    // new card values
    const card_values = {
        'J': 1,
        '2': 2,
        '3': 3,
        '4': 4,
        '5': 5,
        '6': 6,
        '7': 7,
        '8': 8,
        '9': 9,
        'T': 10,
        'Q': 11,
        'K': 12,
        'A': 13
    };

    const find_hand_type = (hand: string) : HandType => {
        const fq: {[key: string]: number} = {};
        let n_j = 0;
        for (let i = 0; i < hand.length; i++) {
            const card = hand[i];
            // don't include J in normal freq counting, count it separately
            if (card == 'J') {
                n_j++;
                continue;
            }
            if (fq[card] == undefined) {
                // card does not exist
                fq[card] = 1;
            }
            else {
                fq[card]++;
            }
        }
        
        const frequencies: number[] = [];
        Object.entries(fq).forEach(entry => {
            frequencies.push(entry[1]);
        });
        frequencies.sort((a, b) => a > b ? -1 : 1);
        
        // since j can mimic any card we will set it to mimic the card which already
        // has the highest frequency for that hand so it will have the best effect in 
        // increasing the hand's power
        if (n_j == 5) return HandType.FIVE;
        else if (frequencies[0] + n_j == 5) return HandType.FIVE;
        else if (frequencies[0] + n_j == 4) return HandType.FOUR;
        else if (frequencies[0] + n_j == 3 && frequencies[1] == 2) return HandType.FULL_HOUSE;
        else if(frequencies[0] + n_j == 3) return HandType.THREE;
        else if (frequencies[0] + n_j == 2 && frequencies[1] == 2) return HandType.TWO_PAIR;
        else if (frequencies[0] + n_j == 2) return HandType.ONE_PAIR;
        else return HandType.HIGH;
    }
    
    hands.sort((a, b) => {
        const hta = find_hand_type(a.hand);
        const htb = find_hand_type(b.hand);
    
        if (hta != htb) {
            if (hta > htb) return -1;
            else return 1;
        }
        else {
            // same type of hand
            for (let i = 0; i < 5; i++) {
                if(card_values[a.hand[i]] > card_values[b.hand[i]]) return -1;
                else if (card_values[a.hand[i]] < card_values[b.hand[i]]) return 1;
                else continue;
            }
            return 0;
        }
    });
    
    let sum = 0;
    hands.forEach((hand, index) => {
        const rank = hands.length - index;
        sum += rank * hand.bid;
        // console.log(`hand: ${hand.hand}, bid: ${hand.bid}, rank: ${rank}, value: ${rank * hand.bid}`);
    })
    
    console.log(sum);
}

part1();
part2();

