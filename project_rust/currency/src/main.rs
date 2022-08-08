use std::io::stdin;

static EURO_TO_DOLLARS:f32 = 1.02;
static DOLLARS_TO_EURO:f32 = 0.98;

fn convert_currency(user_choice:i32) {
    let mut user_input = String::new();

    println!("Whats value do you wants to convert ?\nYour input :");
    stdin().read_line(&mut user_input)
        .ok()
        .expect("Error reading choice");
    if user_choice == 1
    {
        let mut user_input:f32 = user_input.trim().parse().expect("gib a correct number");
        user_input *= EURO_TO_DOLLARS;
        println!("This worth {}$", user_input);
    }
    if user_choice == 2
    {
        let mut user_input:f32 = user_input.trim().parse().expect("gib a correct number");
        user_input *= DOLLARS_TO_EURO;
        println!("This worth {}$", user_input);
    }
}

fn main() {
    println!("Type 1 to convert euro to dollars\nType 2 to convert dollar to euro\nType 3 to exit the program");
    let mut user_choice = String::new();
    while user_choice != "1" && user_choice != "2"
    {
        stdin().read_line(&mut user_choice)
        .ok()
        .expect("Error reading choice");

        user_choice.pop();
        if user_choice == "1"
        {
            convert_currency(1);
        }
        if user_choice == "2"
        {
            convert_currency(2);
        }
        if user_choice == "3"
        {
            break ;
        }
        else if user_choice != "1" && user_choice != "2" && user_choice != "3"
        {
            println!("Input a correct number pls");    
        }
    }
}
