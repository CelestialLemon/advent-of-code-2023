type Race = {
    time: number,
    distance: number
};
const n_ways_to_win_race = (race: Race) :number => {
    let n_ways = 0;
    let n_not_ways = 0;
    for (let t = 0; t <= race.time; t++) {
        // distance = speed * time
        // speed = time spent on button, time = time remaining
        const distance_covered = t * (race.time - t);

        if (distance_covered > race.distance) n_ways++;
        else n_not_ways++;
    }

    console.log(`not result ${n_not_ways}`);
    return n_ways;
}

const part1 = () => {
    const Races: Race[] = [
        { time: 41, distance: 244 },
        { time: 66, distance: 1047 },
        { time: 72, distance: 1228 },
        { time: 66, distance: 1040 } 
    ];
    
    
    let result = 1;
    Races.forEach(race => result *= n_ways_to_win_race(race));
    console.log(`Resuslt: ${result}`);
}

const part2 = () => {
    const race: Race = { time: 41667266, distance: 244104712281040 };
    const result = n_ways_to_win_race(race);
    console.log(`Result: ${result}`);
}

const part2_optimized = () => {
    const a = 1, b = -41667266, c = 244104712281040;
    const x1 = (-b + Math.sqrt((b * b) - (4 * a * c)) / (2 * a) );
    const x2 = (-b - Math.sqrt((b * b) - (4 * a * c)) / (2 * a) );

    const result = Math.floor(x1) - Math.ceil(x2) + 1;
    console.log(`Result: ${result}`);
}

part2_optimized();