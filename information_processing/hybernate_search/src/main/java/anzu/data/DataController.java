package anzu.data;

import anzu.service.StockService;
import anzu.service.StockSearchService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;

import java.util.List;

@Controller
public class DataController {

    @Autowired
    private StockSearchService searchservice;

    @Autowired
    private StockService service;

    @RequestMapping(value = "/", method = RequestMethod.GET)
    public String search(@RequestParam(value = "search", required = false) String q, Model model) {
        List<StockInfo> searchResults = null;
        try {
            service.addTestStockInfo();
            searchResults = searchservice.fuzzySearch(q);

        } catch (Exception ex) {
            throw ex;
        }
        model.addAttribute("search", searchResults);
        return "index";

    }

}
