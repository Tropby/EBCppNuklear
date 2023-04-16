#pragma once

#include <EBNuklear.hpp>
#include <EBObject.hpp>

namespace EBCpp::Nuklear
{
    class EBNuklearWidget : public EBCpp::EBObject<EBNuklearWidget>
    {
        public:
            EBNuklearWidget() : parent(nullptr)
            {

            }

            virtual void render(struct nk_context *ctx) const 
            {
                
            }

            virtual void invalidate()
            {
                if( this->parent != nullptr )
                {
                    this->parent->invalidate();
                }
            }

            void setParent( const EBPtr<EBNuklearWidget> parent ) 
            {
                this->parent = parent;
            }

            EBPtr<EBNuklearWidget> getParent() const
            {
                return parent;
            }        

        private:
            EBPtr<EBNuklearWidget> parent;
    };
}
