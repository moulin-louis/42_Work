use rand::Rng;
use std::io::stdin;

fn main() {
    let mut rng = rand::thread_rng();
    let guess = rng.gen_range(1..101);
    let mut user_guess;

    println!("Type Your guess or Type 'exit' to quit this program");
    while guess > 0
    {
        user_guess = String::from("");

        stdin().read_line(&mut user_guess).ok().expect("Error reading line");
        user_guess.pop();

        if user_guess == "exit" {
            return ;
        }

        let user_guess:i32 = user_guess.trim().parse().expect("Gib number you idiot");

        if user_guess == guess {
            println!("You win congrats");
            return ;
        }

        if user_guess > guess {
            println!("Too much");
        }

        if user_guess < guess {
            println!("Not enough");
        }
    }


}
