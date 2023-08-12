#include <stdexcept>

#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ), buf_() {}

void Writer::push( string data )
{
  for ( auto&& c : data ) {
    if ( capacity_ > size_ ) {
      buf_.push( c );
      size_++;
      push_count_++;
    }
  }
}

void Writer::close()
{
  closed_ = true;
}

void Writer::set_error()
{
  error_ = true;
}

bool Writer::is_closed() const
{
  return closed_;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - size_;
}

uint64_t Writer::bytes_pushed() const
{
  return push_count_;
}

string_view Reader::peek() const
{
  std::string_view sv( &buf_.front(), 1 );
  return sv;
}

bool Reader::is_finished() const
{
  return closed_ && size_ == 0;
}

bool Reader::has_error() const
{
  return error_;
}

void Reader::pop( uint64_t len )
{
  while ( size_ > 0 && len > 0 ) {
    buf_.pop();
    size_--;
    len--;
    pop_count_++;
  }
}

uint64_t Reader::bytes_buffered() const
{
  return size_;
}

uint64_t Reader::bytes_popped() const
{
  return pop_count_;
}
