

#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <cassert>

using namespace std;

class Domain 
{
public:
    Domain(const string& domain) 
    {
        domain_ = { domain.crbegin(), domain.crend() };

        domain_.push_back('.');
    }

    bool operator==(const Domain& other) const 
    {
        return domain_ == other.domain_;
    }

    bool operator<(const Domain& other) const {
        return domain_ < other.domain_;
    }

    bool IsSubdomain(const Domain& other) const {
        const string& other_domain = other.domain_;

        if (domain_.size() > other_domain.size()) {
            return false;
        }

        const string new_other = other.domain_.substr(0, domain_.size());

        return domain_ == new_other;

    }



private:
    string domain_ = ""s;
};

class DomainChecker 
{
public:
    template<typename It>
    DomainChecker(It first, It last) 
    {
        prohibited_domains = { first, last };
        sort(prohibited_domains.begin(), prohibited_domains.end());

        auto last_unique = unique(prohibited_domains.begin(), prohibited_domains.end(),
            [](const Domain& lhs, const Domain& rhs)
            {
                return lhs.IsSubdomain(rhs);
            });

        prohibited_domains.erase(last_unique, prohibited_domains.end());
    }

    bool IsForbidden(const Domain& domain)
    {
        const auto upper = std::upper_bound(prohibited_domains.begin(), prohibited_domains.end(), domain);
        if (upper == prohibited_domains.begin())
        {
            return false;
        }
        else
        {
            return Domain(*(upper - 1)).IsSubdomain(domain);
        }
    }
private:
    vector<Domain> prohibited_domains;
};

template <typename Number>
Number ReadNumberOnLine(istream& input) 
{
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

vector<Domain> ReadDomains(istream& input, size_t number_of_domains) 
{

    string domain;
    vector<Domain> prohibited_domains;

    for (size_t i = 0; i < number_of_domains; ++i) {
        getline(input, domain);
        prohibited_domains.emplace_back(domain);
    }

    return prohibited_domains;
}
void Tests()
{
    stringstream stream;

    stream << "14\n"s
        "mail.ru\n"
        "vk.ru\n"
        "vk.com\n"
        "su\n"
        "text.re.zu\n"
        "cbj.g.wbo\n"
        "caj.g.wbo\n"
        "wes.caj.g.wbo\n"
        "erds.gfgf.g.wbo\n"
        "tytr.ffe.wqeq\n"
        "rte.yt.q\n"
        "yt.q\n"
        "dvs.yt.q\n"
        "aso.uy.qww\n";
    

    const std::vector<Domain> forbidden_domains = ReadDomains(stream, ReadNumberOnLine<size_t>(stream));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    assert(checker.IsForbidden("mail.ru"s));
    assert(checker.IsForbidden("vk.ru"s));
    assert(checker.IsForbidden("su"s));
    assert(checker.IsForbidden("text.re.zu"s));
    assert(checker.IsForbidden("cbj.g.wbo"s));
    assert(checker.IsForbidden("caj.g.wbo"s));
    assert(checker.IsForbidden("wes.caj.g.wbo"s));
    assert(checker.IsForbidden("erds.gfgf.g.wbo"s));
    assert(checker.IsForbidden("tytr.ffe.wqeq"s));
    assert(checker.IsForbidden("rte.yt.q"s));
    assert(checker.IsForbidden("yt.q"s));
    assert(checker.IsForbidden("dvs.yt.q"s));
    assert(checker.IsForbidden("aso.uy.qww"s));

    assert(checker.IsForbidden("wef.mail.ru"s));
    assert(checker.IsForbidden("weasd.vk.ru"s));
    assert(checker.IsForbidden("wefwe.weqqq.su"s));
    assert(checker.IsForbidden("reg.qe.text.re.zu"s));
    assert(checker.IsForbidden("efqqjuj.cbj.g.wbo"s));
    assert(checker.IsForbidden("tyhr.caj.g.wbo"s));
    assert(checker.IsForbidden("sdw.wes.caj.g.wbo"s));
    assert(checker.IsForbidden("wrgwe.erds.gfgf.g.wbo"s));
    assert(checker.IsForbidden("weg.tytr.ffe.wqeq"s));
    assert(checker.IsForbidden("olikum.rte.yt.q"s));
    assert(checker.IsForbidden("qwdff.yt.q"s));
    assert(checker.IsForbidden("olil.dvs.yt.q"s));
    assert(checker.IsForbidden("rthew.aso.uy.qww"s));

    assert(!checker.IsForbidden("erg.ru"s));
    assert(!checker.IsForbidden("wef.ru"s));
    assert(!checker.IsForbidden("jkjls.re.zu"s));
    assert(!checker.IsForbidden("lkos.g.wbo"s));
    assert(!checker.IsForbidden("weioo.g.wbo"s));
    assert(!checker.IsForbidden("iooe.gfgf.g.wbo"s));
    assert(!checker.IsForbidden("wepop.ffe.wqeq"s));
    assert(!checker.IsForbidden("weoll.uy.qww"s));




}

int main() {
    Tests();
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}