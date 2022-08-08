use std::io::stdin;

fn calculate_fract(mut nbr:i32) {
    let mut x = 1;
    let mut result = 1;

    while nbr != 0
    {
        result = result * x;
        nbr -= 1;
        x += 1;
    }
    println!("{}", result);
}

fn main() {
    let mut user_input = String::new();
    stdin().read_line(&mut user_input)
        .ok()
        .expect("Error reading line");
    user_input.pop();
    let user_input:i32 = user_input.trim().parse().expect("gib a correct number");
    calculate_fract(user_input);
}