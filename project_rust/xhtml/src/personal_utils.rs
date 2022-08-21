use std::io::{ stdin, stdout, Result };
use std::fs::File;
use std::io::{Write, Read };

pub fn	get_input() -> String {
    let mut temp = String::new();
    stdin().read_line(&mut temp).unwrap();
    temp.pop();
    temp
}

pub fn	print_line(display_txt:&str) {
    print!("{}", display_txt);
    stdout().flush().unwrap();
}

pub fn open_file(path:String) -> Result<String> {
    let mut content = String::new();
    let mut file = (File::open(path))?;
    (file.read_to_string(&mut content))?;
    Ok(content)
}


pub fn write_file(path:String, file_str:String) {
    let mut file = File::create(path).expect("cant create new file");
    file.write_all(file_str.as_bytes()).expect("write failed");
}
