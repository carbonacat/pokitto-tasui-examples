#ifndef PTE_ACTIVITIES_BASEACTIVITY_HPP
#   define PTE_ACTIVITIES_BASEACTIVITY_HPP


namespace pte::activities
{
    // Base types for all Activities (States in FManga's naming)
    template<typename ActualActivityP>
    class BaseActivity
    {
    public:
        static ActualActivityP& get() noexcept;
    };
}


#endif // PTE_ACTIVITIES_BASEACTIVITY_HPP