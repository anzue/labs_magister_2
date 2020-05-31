package anzu.app;

import anzu.service.StockSearchService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import javax.persistence.EntityManager;

@EnableAutoConfiguration
@Configuration
public class AppConfig {

    @Autowired
    private EntityManager entityManager;

    @Bean
    StockSearchService stockSearchService() {
        StockSearchService stockSearchService = new StockSearchService(entityManager);
        stockSearchService.initializeHibernateSearch();
        return stockSearchService;
    }
}