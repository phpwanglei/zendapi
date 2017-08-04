// Copyright 2017-2018 zzu_softboy <zzu_softboy@163.com>
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Created by zzu_softboy on 2017/08/02.

#ifndef ZAPI_VM_INTERNAL_ABSTRACT_MEMBER_PRIVATE_H
#define ZAPI_VM_INTERNAL_ABSTRACT_MEMBER_PRIVATE_H

#include "zapi/Global.h"
#include <string>

namespace zapi
{
namespace vm
{
namespace internal
{

using zapi::lang::Modifier;

class AbstractMemberPrivate
{
public:
   AbstractMemberPrivate(const AbstractMemberPrivate &other) = default;
   AbstractMemberPrivate(std::string name, Modifier flags)
      : m_flags(flags),
        m_name(name)
   {}
   
   Modifier m_flags;
   std::string m_name;
};

} // internal
} // vm
} // zapi

#endif // ZAPI_VM_INTERNAL_ABSTRACT_MEMBER_PRIVATE_H