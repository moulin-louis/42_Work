pub fn rot13(input:&mut String) -> String {
	let mut result = String::new();

	for mut letter in input.chars() {
		result.push(get_new_char(&mut letter));
	}
	result
}

pub fn decrypt_rot13(input:&mut String) -> String {
	let mut result = String::new();

	for letter in input.chars() {
		result.push((letter as u8 - 13) as char);
	}
	result
}

fn get_new_char(letter:&mut char) -> char {
	*letter = (*letter as u8 + 13) as char;
	*letter
}