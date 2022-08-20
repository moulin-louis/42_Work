use std::io::Write;
use std::io::stdin;
use std::io::stdout;
use itoa;

struct Coin {
    value:i32,
    nbr:i32
}

impl Coin {
   fn get_total_values(&self) ->i32 {
        self.value * self.nbr
    }
}

fn get_nbr_input() ->i32 {
    let mut temp = String::new();
    stdin().read_line(&mut temp).unwrap();
    temp.pop();
    let temp:i32 = temp.trim().parse().expect("Gib a nbr");
    temp
}

fn print_line(display_txt:&str) {
    print!("{}", display_txt);
    stdout().flush().unwrap();
}

fn ft_print_in_euro(result_str:&str) {

    let cts_1;
    let cts_2;

    let mut buffer = result_str.chars().nth(result_str.len() - 1);
    match buffer {
        Some(x) => cts_1 = x,
        None    => {
            print_line("Cant read char\n");
            return ;
        }
    }
    buffer = result_str.chars().nth(result_str.len() - 2);
    match buffer {
        Some(x) => cts_2 = x,
        None    => {
            print_line("Cant read char\n");
            return ;
        }
    }
    let mut result_str = String::from(result_str);
    result_str.pop();
    result_str.pop();

    println!("total value = {}.{}{} Euro", result_str, cts_2, cts_1);
    
}

fn main() {
    let mut coins:Vec<Coin> = Vec::new();

    print_line("Enter amount of money\n");
    print_line("2 Euro : ");
    coins.push(Coin {value:200, nbr:get_nbr_input()});
    print_line("1 Euro : ");
    coins.push(Coin {value:100, nbr:get_nbr_input()});
    print_line("50 cts : ");
    coins.push(Coin {value:50, nbr:get_nbr_input()});
    print_line("20 cts : ");
    coins.push(Coin {value:20, nbr:get_nbr_input()});
    print_line("10 cts : ");
    coins.push(Coin {value:10, nbr:get_nbr_input()});
    print_line("5 cts: ");
    coins.push(Coin {value:5, nbr:get_nbr_input()});

    let mut result = 0;
    for x in 0..coins.len() {
        result += coins[x].get_total_values();
    }
    println!("total value = {} cts", result);
    let mut buffer = itoa::Buffer::new();
    let result_str = buffer.format(result);
    if result_str.len() > 2 {
        ft_print_in_euro(result_str);
    }
}
