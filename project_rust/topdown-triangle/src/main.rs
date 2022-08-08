use std::env;

fn draw_line(lenght:i32) {
    let mut x = 0;
    while lenght != x
    {
        print!("*");
        x += 1;
    }
    println!("");
}

fn main() {
    if env::args().len() != 2 {
        return ; }
    let nbr = String::from(env::args().nth(1).expect("Give a nbr idiot"));
    let mut nbr:i32 = nbr.parse().unwrap();

    while nbr != 0
    {
        draw_line(nbr);
        nbr -= 1;
    }
}
