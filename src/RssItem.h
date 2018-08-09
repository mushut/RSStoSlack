#include <iostream>

class RssItem
{
	friend std::ostream &operator<<(std::ostream &out, const RssItem &item);
public:
	RssItem();
	RssItem(std::string newTitle, std::string newContributor, std::string newDate);
	~RssItem();
	std::string toCsv();
	std::string get_title();
	std::string get_contributor();
	std::string get_date();
private:
	std::string title;
	std::string contributor;
	std::string date;
};
