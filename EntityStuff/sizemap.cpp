//#include "sizemap.h"

//SizeMap::SizeMap()
//{

//}

//SizeMap::Iterator SizeMap::find(size_t key)
//{
//    size_t size = content.size();
//    if(size == 0)
//        return Iterator(content.begin().base());

//    size_t first=0, last =content.size()-1;

//    if(key > content.at(last).first ||
//            key < content.at(first).first)
//        return Iterator(content.begin().base() + size);

//    do
//    {
//        size_t middle = (first + last)/2;
//        Pair & pf = content.at(first);
//        Pair & pm = content.at(middle);
//        Pair & pl = content.at(last);

//        if(pm.first == key)
//            return Iterator(&pm);
//        if(pf.first == key)
//            return Iterator(&pf);
//        if(pl.first == key)
//            return Iterator(&pl);

//        if(pm.first < key)
//            first = middle;
//        else last = middle;
//    }while(first < last);


//    return Iterator(content.begin().base() + size);
//}

//SizeMap::Iterator SizeMap::end()
//{
//    size_t size = content.size();
//    return Iterator(content.begin().base() + size);
//}

//void SizeMap::insert(const SizeMap::Pair &entry)
//{
//    content.push_back(entry);
//    std::sort(content.begin(), content.end(),[](const Pair & p1, const Pair p2){
//        return (p2 >= p1);
//    });
//}

//size_t SizeMap::at(size_t key)
//{
//    Iterator it = find(key);
//    if( it == end())
//        throw std::runtime_error("SizeMap: key <"+ std::to_string(key) + "> doesnt_exist");
//    return it->second;
//}

//void SizeMap::erase(const SizeMap::Iterator &it)
//{
//    auto vit = std::find(content.begin(), content.end(), it.get());
//    if( vit == content.end())
//        throw std::runtime_error("SizeMap: key <"+ std::to_string(it.get().first) + "> doesnt_exist");
//    content.erase(vit);
//}

//SizeMap::Iterator::Iterator(SizeMap::Pair *elem)
//    :elem(elem)
//{

//}

//SizeMap::Iterator::Iterator(const SizeMap::Iterator &other)
//    :elem(other.elem)
//{

//}

//bool SizeMap::Iterator::operator==(const SizeMap::Iterator &other) const
//{
//    return (elem == other.elem);
//}

//bool SizeMap::Iterator::operator!=(const SizeMap::Iterator &other) const
//{
//    return (elem != other.elem);
//}

//SizeMap::Pair * SizeMap::Iterator::operator->()
//{
//    return elem;
//}

//const SizeMap::Pair &SizeMap::Iterator::get() const
//{
//    return *elem;
//}
