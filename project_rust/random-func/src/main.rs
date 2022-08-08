use rand::Rng;

fn  first_fn()
{
    println!("C'est la fonction 1");
}

fn second_fn() {
    println!("C'est la fonction 2")
}

fn third_fn() {
    println!("C'est la fonction 3")
}

fn main() {
    let mut rng = rand::thread_rng();
    let input = rng.gen_range(1..4);

    if input == 1
    {
        first_fn();
    }
    else if input == 2
    {
        second_fn();
    }
    else if input == 3
    {
        third_fn();
    }
}
