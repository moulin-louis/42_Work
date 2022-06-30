use std::io;

fn ft_pustr(str:String)
{
    println!("{}", str);
}

fn main() {
    let mut str = String::new();
    io::stdin()
            .read_line(&mut str)
            .expect("Échec de la lecture de l'entrée utilisateur");
    ft_pustr(str);
}
