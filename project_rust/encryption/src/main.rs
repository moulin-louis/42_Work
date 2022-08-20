mod rot13;

use rot13::rot13;
use rot13::decrypt_rot13;

use std::fs::File;
use std::fs::remove_file;
use std::io::Write;
use std::io::Read;

use std::io::stdin;
use std::io::stdout;

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

fn read_file(path:String) -> String {
    let mut fd = File::open(path).unwrap();
    let mut result = String::new();
    fd.read_to_string(&mut result).unwrap();
    result
}

fn write_file(path:String, file_str:String) {
    let mut file = File::create(path).expect("cant create new file");
    file.write_all(file_str.as_bytes()).expect("write failed");
}

fn main() {
    print_line("Gib the path of the file : ");
    let path = get_input();
    let mut file_str = read_file(path.clone());
    print_line("Type 1 if you want to encrypt your file\nType 2 if you want to decrypt your file\n = ");
    let user_input = get_input();
    if user_input == "1" {
        file_str = rot13(&mut file_str.clone());
    }
    else if user_input == "2" {
        file_str = decrypt_rot13(&mut file_str.clone());
    }
    else {
        print_line("Gib the rigt nbr next time you idiot");
    }
    remove_file(path.clone()).expect("cant remove file");
    write_file(path.clone(), file_str);
}
