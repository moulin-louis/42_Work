use std::io::stdin;
use std::io::stdout;
use std::io::Write;

fn  print_line(display_txt:&str) {
    print!("{}", display_txt);
    stdout().flush().unwrap();
}

fn  get_str_input() -> String {
    let mut str = String::new();
    stdin().read_line(&mut str).unwrap();
    str.pop();
    return str
}

fn  check_input(user_input:String) -> i32 {
    for c in user_input.chars() {
        if c.is_alphabetic() == false {
            print_line("Gib alphabetic string pls\n");
            return 0
        }
    }
    if user_input.len() == 1 || user_input.len() == 2 {
        print_line("Gib a bigger string pls\n");
        return 0
    }
    return 1
}

fn  reverse_array(second_half:&mut String) -> String {
    let result:String = second_half.chars().rev().collect();
    result
}

fn  check_palindrome(user_input:&mut String) {
    let first_half:String;
    let mut second_half:String;

    if user_input.len() % 2 == 0 {
        user_input.insert(user_input.len() / 2, ' ');
        let v: Vec<&str> = user_input.split(' ').collect();
        first_half = String::from(v[0]);
        second_half = String::from(v[1]);
        second_half = reverse_array(&mut second_half);
        if first_half == second_half {
            print_line("Its a palindrome");
            return ;
        }
        print_line("Its not a palindrome");
    }
    else if user_input.len() % 2 == 1 {
        let len = user_input.len()/ 2;
        user_input.replace_range(len..(len + 1), " ");
        let v: Vec<&str> = user_input.split(' ').collect();
        first_half = String::from(v[0]);
        second_half = String::from(v[1]);
        second_half = reverse_array(&mut second_half);
        if first_half == second_half {
            print_line("Its a palindrome");
            return ;
        }
        print_line("Its not a palindrome");
    }
}

fn main() {
    print_line("Input your word : ");
    let mut user_input = get_str_input();
    if check_input(user_input.clone()) == 0 {
        print_line("Error in your input");
        return ;
    }
    check_palindrome(&mut user_input);
}
