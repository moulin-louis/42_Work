use std::io::Result;
use std::io::Write;
use std::io::Read;
use std::fs::File;

use std::env;
use std::io::stdin;
use std::io::stdout;
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize, Debug)]
struct  Question {
    question:String,
    answer:String,
}

fn get_input() -> String {
    let mut temp = String::new();
    stdin().read_line(&mut temp).unwrap();
    temp.pop();
    temp
}

fn print_line(display_txt:&str) {
    print!("{}", display_txt);
    stdout().flush().unwrap();
}

fn open_file(path:String) -> Result<String> {
    let mut content = String::new();
    let mut file = (File::open(path))?;
    (file.read_to_string(&mut content))?;
    Ok(content)
}

fn get_questions(path:String) -> Vec<Question> {
    let questions = match open_file(path) {
        Err(e) => panic!("Failed to read file {:?}", e),
        Ok(result) => {
            let questions: Vec<Question> = match serde_json::from_str(&result) {
                Err(e) => panic!("fail to decode json {:?}", e), 
                Ok(quesions) => quesions
            };
            questions
        }
    };
    questions
}

fn get_answer(questions:Vec<Question>) ->Vec<String> {
    let mut user_answer:Vec<String> = Vec::new();
    for i in questions {
        print_line(i.question.as_str());
        user_answer.push(get_input());
    }
    user_answer
}

fn calculate_score(questions:Vec<Question>, user_answer:Vec<String>) -> i32 {
    let mut score = 0;
    let mut i = 0;
    for x in questions {
        if x.answer == user_answer[i] {
            score += 1;
        }
        i += 1;
    }
    score
}

fn main() {
    if env::args().len() != 2 {
        print_line("Gib just the path of the file next time\n");
        return ;
    }
    let questions = get_questions(env::args().nth(1).unwrap());
    let temp = get_questions(env::args().nth(1).unwrap());
    let user_answer = get_answer(questions);
    let score = calculate_score(temp, user_answer);
    if score == 0 {
        print_line("You suck looser\n");
        return ;
    }
    println!("You score is {}", score);

}
