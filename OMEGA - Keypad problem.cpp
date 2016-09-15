import java.util.*;
import java.math.*;

public class Main{
    static BigInteger x, y, d;
    public static void egcd(BigInteger a, BigInteger b){
        if (b.compareTo(BigInteger.ZERO) == 0){
            x = BigInteger.ONE;
            y = BigInteger.ZERO;
            d = a;
            return;
        }
        egcd(b, a.mod(b));
        BigInteger x1 = y;
        BigInteger y1 = x.subtract((a.divide(b)).multiply(y));
        x = x1;
        y = y1;
    }
    static int cont = 0;
    public static void main(String [] args){
        Scanner leer = new Scanner(System.in);
        while (leer.hasNext()){
            cont++;
            int n = leer.nextInt();
            BigInteger r = leer.nextBigInteger();
            x = BigInteger.ZERO;
            y = BigInteger.ZERO;
            d = BigInteger.ZERO;
            //BigInteger n = leer.nextBigInteger();
            //BigInteger r = leer.nextBigInteger();
            if (n == 0) 
                if (r.compareTo(BigInteger.ZERO) == 0)
                    break;
            BigInteger a[] = new BigInteger[n + 5];

            for (int i = 0; i < n; i++){
                a[i] = leer.nextBigInteger();
            }

            BigInteger sol[] = new BigInteger[n + 5];
            sol[0] = BigInteger.ONE;
            for (int i = 1; i < n; i++){
                sol[i] = BigInteger.ZERO;
            }

            BigInteger gcd = a[0];
            for (int i = 1; i < n; i++){
                egcd(gcd, a[i]);
                gcd = d;
                sol[i] = y;

                for (int j = 0; j <= i - 1; j++){
                    sol[j] = sol[j].multiply(x);
                }
            }

            if ((r.mod(gcd)).compareTo(BigInteger.ZERO) == 0){
                System.out.print("Case #" + cont + ":");
                for (int i = 0; i < n; i++){
                    String s = " " + (sol[i].multiply(r)).divide(gcd);
                    System.out.print(s);
                }
                System.out.println("");
            }else{
                System.out.println("Case #" + cont + ": Stupid keypad!");
            }
        }
    }
}
