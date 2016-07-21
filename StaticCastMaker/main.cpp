
#include <string>
#include <vector>
#include <fstream>
#include <utility>
using namespace std::string_literals;

std::string types[]{
    "bool"s,
    "std::int32_t"s,
    "std::int64_t"s,
    "std::int16_t"s,
    "std::int8_t"s,
    "std::uint32_t"s,
    "std::uint64_t"s,
    "std::uint16_t"s,
    "std::uint8_t"s,
    "char"s,
    "char16_t"s,
    "char32_t"s,
    "float"s,
    "double"s,
    "long double"s,
};

auto
make_list() {

    std::vector<std::pair<std::string,std::string>> ans;
    constexpr std::uint32_t varSize=sizeof(types)/sizeof(std::string);
    ans.reserve(varSize*(varSize-1));

    for (std::uint32_t varI=0; varI<varSize; ++varI) {
        for (std::uint32_t varJ=0; varJ<varSize; ++varJ) {
            if (varI==varJ) { continue; }
            auto varTemp=std::make_pair(types[varI],types[varJ]);
            ans.push_back(varTemp);
        }
    }

    return std::move(ans);
}

int main(int,char **) {

    auto about_to_print=make_list();
    std::ofstream stream("static_cast_base.txt");
    /*
    //from:std::double_t to:std::float_t
    cast_functions_[make_pair_from_to<std::double_t,std::float_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::double_t*>(arg.get()));
        auto * varTo=new auto(static_cast<std::float_t>(varFrom));
        return{typeid(std::float_t),std::shared_ptr<std::float_t>(varTo)};
    };
    */

    for (const auto &varI:about_to_print) {

        stream<<"/* from:"<<varI.first<<" to:"<<varI.second<<" */"<<std::endl;
        stream<<"cast_functions_[make_pair_from_to<";
        stream<<varI.first;
        stream<<",";
        stream<<varI.second;
        stream<<">()]=[](const SharedVoidType&arg)->RuntimeType {";
        stream<<std::endl;

        stream<<"const auto & varFrom=*(reinterpret_cast<const ";
        stream<<varI.first<<"*>(arg.get()));"<<std::endl;

        stream<<"auto * varTo=new auto(static_cast<";
        stream<<varI.second<<">(varFrom));"<<std::endl;

        stream<<"return{typeid("<<varI.second<<"),std::shared_ptr<"
            <<varI.second<<">(varTo)};"<<std::endl;

        stream<<"};";

        stream<<std::endl;
        stream<<std::endl;


    }

}
