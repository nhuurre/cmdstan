#ifndef CMDSTAN_WRITE_PROFILING_HPP
#define CMDSTAN_WRITE_PROFILING_HPP

#include <stan/math/rev/core/profiling.hpp>
#include <stan/callbacks/writer.hpp>
#include <stan/version.hpp>
#include <string>
#include <vector>

namespace cmdstan {
void write_profiling(stan::callbacks::writer& writer,
                     stan::math::profile_map& p) {
    stan::math::profile_map::iterator it;
    std::stringstream profile_csv_stream;
    profile_csv_stream << "name,thread_id,time,forward_time,reverse_time,chain_stack,no_chain_stack,autodiff_calls,no_autodiff_calls" << std::endl;
    for (it = p.begin(); it != p.end(); it++) {
        profile_csv_stream 
            // name
            <<  it->first.first << ","
            // thread_id
            << it->first.second << ","  //
            // time_total
            << (it->second.get_fwd_time() + it->second.get_rev_time()) << ","
            // forward_time
            << it->second.get_fwd_time() << ","
            // reverse_time
            << it->second.get_rev_time() << ","
            // chain_stack_total
            << it->second.get_chain_stack_used() << ","
            // nochain_stack_total
            << it->second.get_nochain_stack_used() << ","
            // autodiff_passes
            << it->second.get_num_rev_passes()  << ","
            // no_autodiff_passes
            << it->second.get_num_no_AD_fwd_passes()
            << std::endl;
    }
    writer(profile_csv_stream.str());
}
}  // namespace cmdstan
#endif
