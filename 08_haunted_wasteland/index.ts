import { readFileSync } from "node:fs";

const instructions = 'LLRLRRLLRLRRLLRLRRLRRRLRLRLRRRLLRLRRRLRLRRRLRLRLLLRRLRLRLLRLRRLRRRLRRRLLRRLRLRRRLRRLRRRLRLLRRLRRRLRRRLRRLRLRRLLLRLRLLRRRLRRLLRLRLRRLLRLRRLLRLRRLRRLLRRRLRLRLRRRLLRRRLRRLRRRLRRRLRLRRRLRRLLLRRRLRLLLRRRLRLLRLLRRRLLRRLRRRLRRRLRLLRLRLRRRLLRRLRRRLRRLRLLRRRLRRLRRRLRRRLRRRLRLRRRLRRRLRLRRRR';

const data = readFileSync('data.txt', 'utf-8').split('\n');

const nodes: {[key: string]: { left: string, right: string }} = {};
data.forEach(line => {
    const node = line.substring(0, 3);
    const left = line.substring(7, 10);
    const right = line.substring(12, 15);

    nodes[node] = {
        'left': left,
        'right': right
    };
});

const part1 = () => {
    const find_steps_till_end = (): number => {
        let n_steps = 0;
        let current_node = 'AAA';
    
        while (current_node != 'ZZZ') {
            const instrcution = instructions[n_steps % instructions.length];
            if (instrcution === 'L') {
                current_node = nodes[current_node].left;
                n_steps++;
            }
            else if (instrcution === 'R') {
                current_node = nodes[current_node].right;
                n_steps++;
            }
            // console.log(current_node);
            // if (n_steps > 100) return 0;
        }
        return n_steps;
    }
    console.log(find_steps_till_end());
}

const part2 = () => {
    const current_nodes: string[] = [];

    Object.entries(nodes).forEach(entry => {
        if (entry[0][2] === 'A') {
            current_nodes.push(entry[0]);
        }
    });
    console.log(current_nodes);

    let n_steps = 0;
    let n_prev_steps = 0;
    while(true) {
        let goal_reached = true;
        current_nodes.forEach(node => {
            if (node[2] != 'Z') goal_reached = false;
        });
        if (goal_reached) break;

        const instruction = instructions[n_steps % instructions.length];

        for (let i = 0; i < current_nodes.length; i++) {
            if (instruction === 'L') {
                n_steps++;
                current_nodes[i] = nodes[current_nodes[i]].left;
            }
            else if (instruction === 'R') {
                current_nodes[i] = nodes[current_nodes[i]].right;
                n_steps++;
            }
        }

        if (n_steps - n_prev_steps >= 10e6) {
            console.log(`${n_steps / 10e6} done`);
            n_prev_steps = n_steps;
        }
        
    }

    console.log(n_steps);
}

const part3 = () => {
    const cns = [ 'KLA', 'AAA', 'NDA', 'LBA', 'NNA', 'QVA' ];

    const find_steps_till_end = (cn: string): number => {
        let n_steps = 0;
        let current_node = cn;
    
        while (current_node[2] != 'Z') {
            const instrcution = instructions[n_steps % instructions.length];
            if (instrcution === 'L') {
                current_node = nodes[current_node].left;
                n_steps++;
            }
            else if (instrcution === 'R') {
                current_node = nodes[current_node].right;
                n_steps++;
            }
            // console.log(current_node);
            // if (n_steps > 100) return 0;
        }
        return n_steps;
    }
    
    cns.forEach(cn => console.log(find_steps_till_end(cn)));
}

part3();

