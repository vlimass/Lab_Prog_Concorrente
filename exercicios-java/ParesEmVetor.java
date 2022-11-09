import java.util.Random;

class Vetor {
    // recursos compartilhados
    final int tamVetor = 100;
    int totalPares = 0; 
    private Integer[] vetor;

    // instância para geração de números randômicos 
    Random rand = new Random();

    // construtor 
    public Vetor() { 
        this.vetor = new Integer[tamVetor];
        
        // preenche o vetor com um inteiro aleatório menor que 1000000000
        for (int i = 0; i < tamVetor; i++) {
            this.vetor[i] = rand.nextInt(1000000000); 
        }
    }

    public void imprime() {
        System.out.println("Valores do vetor");
        System.out.println("----------------");
        for (int i = 0; i < tamVetor; i++) {
            System.out.println(i + " : " + vetor[i]);
        }
        System.out.println("----------------");
    }
    
    public synchronized void verificaSePar(int index) {
        if(vetor[index] % 2 == 0) {
            totalPares++;
        }
    }

    public synchronized int getTotalPares() {
        return totalPares;
    }

}

//classe que implementa a tarefa de cada thread do programa 
class tarefaThreads extends Thread {
    private int id; // identificador da thread
    private int nThreads;
    Vetor vet;


    // construtor
    public tarefaThreads(int tid, int numThreads, Vetor vetor) {
        this.id = tid;
        this.nThreads = numThreads;
        this.vet = vetor;
    }

    public void run() {
        for (int i = id; i < vet.tamVetor; i += nThreads){
            vet.verificaSePar(i);
        }
    }
}  

class ParesEmVetor {
    static final int numThreads = 10;

    public static void main(String[] args) {
        //reserva espaço para um vetor de threads
        Thread[] threads = new Thread[numThreads];

        // instância do vetor compartilhado entre as threads
        Vetor vetor = new Vetor();
        
        // cria as threads da aplicacao
        for (int i=0; i<threads.length; i++) {
            threads[i] = new tarefaThreads(i, numThreads, vetor);
        }

        // inicia as threads
        for (int i=0; i<threads.length; i++) {
            threads[i].start();
        }

        //espera pelo termino de todas as threads
        for (int i=0; i< threads.length; i++) {
            try { 
                threads[i].join(); 
            } catch (InterruptedException e) { return; }
        }

        vetor.imprime(); // imprime o vetor gerado
        
        System.out.println("Total de pares: " + vetor.getTotalPares());
    }
}