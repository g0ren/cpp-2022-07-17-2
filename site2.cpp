#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Site {
public:
	virtual void access()=0;
	virtual void addPage(string)=0;
	virtual ~Site() {
	}
};

class SinglePage: public Site {
	string page;
public:
	SinglePage(string page = "") {
		this->page = page;
	}
	void addPage(string page) {
		this->page = page;
	}
	void access() {
		cout << "Single page site" << endl;
		cout << page << endl;
		cout << endl;
	}
};

class MultiPage: public Site {
	vector<string> pages;
public:
	MultiPage(string page = "") {
		this->pages.push_back(page);
	}
	void addPage(string page) {
		if (this->pages[0] != "")
			this->pages.push_back(page);
		else
			this->pages[0] = page;
	}
	void access() {
		cout << "Multi page site" << endl;
		for (auto page : this->pages)
			cout << page << endl;
		cout << endl;
	}
};

class SiteFactory {
public:
	virtual Site* makeSite(string)=0;
	virtual ~SiteFactory() {
	}
};

class SinglePageFactory: public SiteFactory {
public:
	Site* makeSite(string page) {
		return new SinglePage(page);
	}
};

class MultiPageFactory: public SiteFactory {
public:
	Site* makeSite(string page) {
		return new MultiPage(page);
	}
};

class MultiPageBuilder {
	MultiPageFactory *factory;
	Site *site;
public:
	MultiPageBuilder() {
		this->factory = new MultiPageFactory;
		this->site = this->factory->makeSite("");
	}
	void addPage(string page) {
		this->site->addPage(page);
	}
	Site* getSite() {
		return this->site;
	}
};

class MultiPageDirector {
	queue<string> pages;
	MultiPageBuilder *builder;
public:
	MultiPageDirector() {
		this->builder = new MultiPageBuilder;
	}
	void addPage(string page) {
		this->pages.push(page);
	}
	Site* build() {
		while (!pages.empty()) {
			this->builder->addPage(pages.front());
			pages.pop();
		}
		return this->builder->getSite();
	}
};

int main() {
	string page = "<i>Hello world!</i>";
	SinglePageFactory sf;
	Site *s = sf.makeSite("<i>Hello world!</i>");

	MultiPageDirector md;
	md.addPage("<h1>This is a motherfucking website.</h1>");
	md.addPage("<aside>And it's fucking perfect.</aside>");
	md.addPage("<h2>Seriously, what the fuck else do you want?</h2>");
	md.addPage("<p>You never knew it, but this is your perfect website.</p>");
	md.addPage("<h3>Yes, this is fucking satire, you fuck</h3>");
	Site *m = md.build();

	s->access();
	m->access();

	return 0;
}
