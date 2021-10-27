// Dichiarazione funzioni di IO

/* Inizializza la seriale*/
void serial_setup(int baud);

//legge il comando dalla seriale e lo scrive nella struct
//comando = lettera + intero
void read_command(t_cmd* command_ptr);

//
void write_command(t_cmd* command_ptr);

