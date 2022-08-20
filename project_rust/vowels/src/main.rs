use std::env;

fn main() {
    let user_input = String::from(env::args().nth(1).expect("cant read env args or run with arg"));

    let mut vowels_count = 0;
    let mut consonant_count = 0;

    let vowel = vec!['a', 'o', 'i', 'e', 'u', 'y'];

    for c in user_input.chars()
    {
        if c.is_alphabetic()
        {
            if vowel.contains(&c)
            {
                vowels_count += 1;
            }
            else
            {
                consonant_count += 1;    
            }
        }
    }
    println!("vowel = {}\nconsonant = {}", vowels_count, consonant_count);

}
