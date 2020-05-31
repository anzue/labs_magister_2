package anzu.data;

import org.hibernate.search.annotations.Field;
import org.hibernate.search.annotations.Indexed;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Indexed
@Entity
public class StockInfo {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private long id;
    @Field
    private String symbol;
    @Field
    private String name;
    @Field
    private double stock;

//    public StockInfo(){}
//
//    public StockInfo(String symlol_, String name_, double stock_) {
//        symbol = symlol_;
//        name = name_;
//        stock = stock_;
//    }

    public long getId(){return id;}

    public String getSymbol() {
        return symbol;
    }

    public StockInfo withSymbol(String symbol_) {
        symbol = symbol_;
        return this;
    }

    public String getName() {
        return name;
    }

    public StockInfo withName(String name_) {
        name = name_;
        return this;
    }

    public double getStock() {
        return stock;
    }

    public StockInfo withStock(double stock_) {
        stock = stock_;
        return this;
    }
}
