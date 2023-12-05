import { readFileSync } from 'node:fs';

/**
 * s - source index
 * d - destination index
 * l - length of mapping
 */
type MappingInfo = {
    s: number,
    d: number,
    l: number
};

const data = readFileSync('data.txt', 'utf-8');
const data2 = data.split('```');

/**
 * What is contained in various indexes
 *  1 - all the seeds
 *  3 - seed to soil mappings
 *  5 - soil to fertilizer mappings
 *  7 - fertilizer to water mapping
 *  9 - water to light mapping
 * 11 - light to temperature mapping
 * 13 - temperature to humidity mapping
 * 15 - humidity to location mapping
 */

const all_mappings: MappingInfo[][] = [];

for (let it = 3; it <= 15; it += 2) {
    const mapping_data = data2[it];
    const mappings: MappingInfo[] = [];
    mapping_data.split('\n').forEach(mapping_line => {
        const [d, s, l] = mapping_line.split(' ').map(n => parseInt(n));
        const mi: MappingInfo = { d: d, s: s, l: l };
        mappings.push(mi);
    })

    all_mappings.push(mappings);
}

const find_mapping = (n: number, map: MappingInfo[]): number => {
    for (let i = 0; i < map.length; i++) {
        const mi = map[i];
        const source_lower_bound = mi.s, source_upper_bound = mi.s + mi.l - 1;
        if (n >= source_lower_bound && n <= source_upper_bound) {
            // mapping found
            return n + (mi.d - mi.s);
        }
    }
    return n;
}

const part1 = () => {
    const seeds = data2[1].split(' ').map(n => parseInt(n));
    let min_location = Number.MAX_SAFE_INTEGER;

    seeds.forEach(seed => {
        let current_map_value = seed;
        all_mappings.forEach(mapping => {
            current_map_value = find_mapping(current_map_value, mapping);
        });
        min_location = Math.min(min_location, current_map_value);
    })
    console.log(min_location);
}

const part2 = () => {
    const seeds_string = data2[1].split(' ');
    let min_location = Number.MAX_SAFE_INTEGER;
    // const seeds: number[] = [];
    for (let i = 0; i < seeds_string.length; i += 2) {
        const [s, l] = [parseInt(seeds_string[i]), parseInt(seeds_string[i + 1])];
        for (let si = s; si < s + l; si++) {
            let current_map_value = si;
            all_mappings.forEach(mapping => {
                current_map_value = find_mapping(current_map_value, mapping);
            });
            min_location = Math.min(min_location, current_map_value);
        }
        console.log(`index ${i} done`);
    }
    console.log(min_location);
    // took 6mins 43 secs to run
}

// part1();
part2();
