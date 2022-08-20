use std::io::stdin;
use std::f64::consts::PI;

fn calculate_from_radius() {
	let mut user_nbr = String::new();
	println!("Your input = ");

	stdin().read_line(&mut user_nbr).unwrap();
	user_nbr.pop();

	let user_nbr:i32 = user_nbr.parse().expect("gib a nbr you idiot");
	println!("radius ={}, diameter = {}, aera = {}", user_nbr, user_nbr * 2, PI * (user_nbr / 2) as f64);
}

fn calculate_from_diameter() {
	let mut user_nbr = String::new();
	println!("Your input = ");

	stdin().read_line(&mut user_nbr).unwrap();
	user_nbr.pop();

	let user_nbr:i32 = user_nbr.parse().expect("gib a nbr you idiot");
	println!("radius ={}, diameter = {}, aera = {}", user_nbr / 2, user_nbr, PI * (user_nbr / 4) as f64);
}

fn calculate_from_aera() {
	let mut user_nbr = String::new();
	println!("Your input = ");

	stdin().read_line(&mut user_nbr).unwrap();
	user_nbr.pop();
	let mut user_nbr:f64 = user_nbr.parse().expect("gib a nbr you idiot");
	user_nbr = (user_nbr/PI).sqrt();
	println!("radius ={}, diameter = {}, aera = {}", radius, radius as i32 * 2, user_nbr);
}

fn	main() {
	let mut user_input = String::new();


	while user_input != "exit"
	{
		println!("\n- Type 1 to input radius
		\n- Type 2 to input diameter
		\n- Type 3 to input aera
		\n- Type exit to exit the program");
		user_input = String::from("");
		stdin().read_line(&mut user_input).unwrap();
		user_input.pop();

		if user_input == "1"
		{
			calculate_from_radius();
		}
		else if user_input == "2"
		{
			calculate_from_diameter();
		}
		else if user_input == "3"
		{
			calculate_from_aera();
		}
		else if user_input != "exit"
		{
			println!("Gib a goob nbr you idiot");
		}
	}
	println!("Exiting the program");
}