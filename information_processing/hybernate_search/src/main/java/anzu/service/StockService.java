package anzu.service;

import anzu.data.Repo;
import anzu.data.StockInfo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@Service
public class StockService {

    @Autowired
    Repo repo;
    // data from https://www.nasdaq.com/market-activity/stocks/screener
    List<StockInfo> knownStocks = Arrays.asList(
            new StockInfo().withSymbol("MSFT").withName("Microsoft Corporation Common Stock").withStock(183.25),
            new StockInfo().withSymbol("AAPL").withName("Apple Inc. Common Stock").withStock(317.94),
            new StockInfo().withSymbol("AMZN").withName("Amazon.com, Inc. Common Stock").withStock(2442.37),
            new StockInfo().withSymbol("GOOGL").withName("Alphabet Inc. Class A Common Stock").withStock(1433.52)
    );

    public void addTestStockInfo() {
        for (StockInfo info : knownStocks) {
            repo.save(info);
        }
    }

}
