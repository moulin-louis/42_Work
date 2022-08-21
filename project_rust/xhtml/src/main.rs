mod personal_utils;

use personal_utils::{open_file, print_line};
use std::env;
use regex::Regex;

fn remove_tag(user_file: String) -> String {
    let re_tag = Regex::new(r"(</?[^>]+>)").unwrap();
    let re_nl = Regex::new(r"(\n\s+)").unwrap();

    let modified = re_tag.replace_all(&user_file[..], "");
    let result = String::from(re_nl.replace_all(&modified[..], "\n"));
    result
}

fn main() {
    if env::args().len() != 2 {
        print_line("Gib ./xhtml path_to_file next time you idiot");
        return ;
    }
    let user_file = match open_file(env::args().nth(1).unwrap())
    {
        Err(e) => panic!("Failed to read file  {:?}", e),
        Ok(result) => result
    };
    let result = remove_tag(user_file);
    println!("{}", result);
}
