import java.util.Random;

class Buffer {
    static final int N = 5; //tamanho do buffer
    private double[] buffer = new double[N]; // buffer compartilhado 

    private int count = 0; // número de posições ocupadas pelo buffer
    private int in = 0; 
    private int out = 0; 

    // construtor
    Buffer() {
        for(int i = 0; i < N; i++){
            this.buffer[i] = 0; 
        }
    }

    // imprime o buffer
    public synchronized void imprime() {
        for(int i = 0; i < N; i++){
            System.out.print(buffer[i] + " ");
        }
        System.out.print("\n");
    }

    // insere um item 
    public synchronized void Insere(double item, int id) {
        try {
            while(count == N){
                // bloqueia se buffer ocupado 
                System.out.println("Produtor[" + id + "] bloqueou");
                wait();
            }
    
            this.buffer[in] = item;
            in = (in + 1) % N;
            count++;

            System.out.println("Produtor[" + id + "] produziu");
            imprime(); // imprime o buffer
            
            // libera as threads bloqueadas da fila de espera
            notifyAll(); 
        } catch (InterruptedException e) { return; }
    }

    // remove um item 
    public synchronized double Remove(int id) {
        double item;

        try {
            while(count == 0){
                // bloqueia se buffer vazio 
                System.out.println("Consumidor[" + id + "] bloqueou");
                wait();
            }

            item = this.buffer[out];
            this.buffer[out] = 0;
            out = (out + 1) % N;
            count--;

            System.out.println("Consumidor[" + id + "] consumiu");
            imprime(); // imprime o buffer

            // libera as threads bloqueadas da fila de espera
            notifyAll(); 

            return item;
        } catch (InterruptedException e) { return -1; }
    }
}


class Produtor extends Thread {
    private int id; // identificador da thread
    Buffer buffer;

    // instância para geração de números randômicos 
    Random rand = new Random();

    Produtor(int tid, Buffer buff) {
        this.id = tid;
        this.buffer = buff;
    }

    // método main da thread
    public void run() {
        while(true) {
            // produzindo item 
            buffer.Insere(rand.nextDouble(), id);
            try {
                sleep(1000);
            } catch (InterruptedException e) { return ; }
        }
    }
}

class Consumidor extends Thread {
    private int id; // identificador da thread
    Buffer buffer;

    Consumidor(int tid, Buffer buff) {
        this.id = tid;
        this.buffer = buff;
    }

    // método main da thread
    public void run() {
        while(true) {
            // produzindo item 
            buffer.Remove(id);
            try {
                sleep(1000);
            } catch (InterruptedException e) { return ; }
        }
    }
}


class ProdutorConsumidor {
    static final int numProdutores = 3, numConsumidores = 3;
    public static void main(String[] args) {
        //reserva espaço para um vetor de threads
        Thread[] produtores = new Thread[numProdutores];
        Thread[] consumidores = new Thread[numConsumidores];

        // instância do buffer compartilhado entre as threads
        Buffer buffer = new Buffer();

        // cria e inicia os produtores da aplicação 
        for(int i = 0; i < produtores.length; i++){
            produtores[i] = new Produtor(i + 1, buffer);
            produtores[i].start();
        }

        // cria e inicia os consumidores da aplicação 
        for(int i = 0; i < consumidores.length; i++){
            consumidores[i] = new Consumidor(i + 1, buffer);
            consumidores[i].start();
        }
    }
}
