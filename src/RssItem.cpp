#include <string>
#include <iostream>

#include "RssItem.h"

RssItem::RssItem()
{
}

RssItem::RssItem(std::string newTitle, std::string newContributor, std::string newDate)
{
	title = newTitle;
	contributor = newContributor;
	date = newDate;
}

RssItem::~RssItem()
{
}

std::ostream &operator<<(std::ostream &out, const RssItem &item)
{
	out << item.title << " - " << item.contributor << " - " << item.date << "\\n\\n";
	return out;
}

std::string RssItem::toCsv()
{
	std::string result = title + ";" + contributor + ";" + date + ";";
	return result;
}

std::string RssItem::get_title()
{
	return title;
}

std::string RssItem::get_contributor()
{
	return contributor;
}

std::string RssItem::get_date()
{
	return date;
}
