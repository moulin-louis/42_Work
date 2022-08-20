use std::env;

fn main() {
    let input = String::from(env::args().nth(1).expect("Cant read argv"));
    let input:i32 = input.trim().parse().expect("Gib nbr you idiot");

    let mut first = 0;
    let mut second = 1;
    let mut temp ;
    while second < input
    {
        temp = second;
        second = second + first;
        if second < input
        {
            print!(" {}", second);
        }
        first = temp;
    }
}
