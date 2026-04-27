#pragma once

#include "../st6.h"

class AttribStackNode;
class ClipNode;
class ImageNode;
class JustifyNode;
class NullNode;
class ParagraphNode;
class PositionNode;
class RDLReNode;
class StyleNode;
class TRANode;
class TextNode;
class TextPtrNode;
struct tagRECT;

class IMPORT RDLNode
{
    public:
        RDLNode(const RDLNode&);
        RDLNode();
        virtual ~RDLNode();
        RDLNode& operator=(const RDLNode&);

        virtual operator AttribStackNode*();
        virtual operator ClipNode*();
        virtual operator ImageNode*();
        virtual operator JustifyNode*();
        virtual operator NullNode*();
        virtual operator ParagraphNode*();
        virtual operator PositionNode*();
        virtual operator RDLReNode*();
        virtual operator StyleNode*();
        virtual operator TRANode*();
        virtual operator TextNode*();
        virtual operator TextPtrNode*();
        virtual operator const AttribStackNode*() const;
        virtual operator const ClipNode*() const;
        virtual operator const ImageNode*() const;
        virtual operator const JustifyNode*() const;
        virtual operator const NullNode*() const;
        virtual operator const ParagraphNode*() const;
        virtual operator const PositionNode*() const;
        virtual operator const RDLReNode*() const;
        virtual operator const StyleNode*() const;
        virtual operator const TRANode*() const;
        virtual operator const TextNode*() const;
        virtual operator const TextPtrNode*() const;
};

class IMPORT TextRenderContext
{
    public:
        class Image;
        struct FontDesc;

        TextRenderContext(const TextRenderContext&);
        TextRenderContext();
        virtual ~TextRenderContext();
        TextRenderContext& operator=(const TextRenderContext&);
        void clear_default_attributes();
        const struct TextRenderAttributes& get_current_attributes();
        const TextRenderAttributes& get_default_attributes();
        int get_origin_h();
        int get_origin_v();
        int get_pos_h();
        int get_pos_v();
        void pop_default_attributes();
        void pop_state();
        void push_default_attributes();
        void push_state();
        void reset_to_default();
        void set_current_attributes(const TextRenderAttributes&);
        void set_default_attributes(const TextRenderAttributes&);
        void set_origin(int, int);
        void set_origin_h(int);
        void set_origin_v(int);
        void set_pos(int, int);
        void set_pos_h(int);
        void set_pos_v(int);

    private:
        void get_state(struct State&);
        void set_state(const State&);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT RenderDisplayList
{
    public:
        RenderDisplayList(const RenderDisplayList&);
        RenderDisplayList();
        ~RenderDisplayList();
        RenderDisplayList& operator=(const RenderDisplayList&);
        void execute(TextRenderContext&, bool);
        void get_dimensions(TextRenderContext&, f32&, f32&, f32&);
        int get_element_count() const;
        bool get_element_pos(TextRenderContext&, int, f32&, f32&, f32&);
        void optimize();
        void update(f32);

        st6::list<RDLNode*> nodes;
};

// TODO: What do the four visual size values mean?
struct VisualSize
{
        unsigned a;
        unsigned b;
        unsigned c;
        unsigned d;
};

class IMPORT ClipNode : public RDLNode
{
    public:
        ClipNode(const tagRECT&);
        ClipNode(const ClipNode&);
        ClipNode();
        virtual ~ClipNode();
        ClipNode& operator=(const ClipNode&);
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, u32, RDLNode*&, RDLNode*&) const;
        virtual void Update(f32);
        const tagRECT& get_rect();
        void set_rect(const tagRECT&);

        virtual operator ClipNode*();
        virtual operator const ClipNode*() const;

        unsigned unk04;
        unsigned unk08;
        unsigned unk0C;
        unsigned unk10;
};

class IMPORT NullNode : public RDLNode
{
    public:
        NullNode(const NullNode&);
        NullNode();
        virtual ~NullNode();
        NullNode& operator=(const NullNode&);
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, u32, RDLNode*&, RDLNode*&) const;
        virtual void Update(f32);

        virtual operator NullNode*();
        virtual operator const NullNode*() const;
};

class IMPORT StyleNode : public RDLNode
{
    public:
        StyleNode(const StyleNode&);
        StyleNode(u16);
        StyleNode();
        virtual ~StyleNode();
        class StyleNode& operator=(class StyleNode const&);
        virtual class RDLNode* Clone() const;
        virtual void Execute(class TextRenderContext&, bool);
        virtual void GetElementPos(int, class TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(class TextRenderContext const&, struct VisualSize&) const;
        virtual bool SplitAtSize(class TextRenderContext const&, int, u32, class RDLNode*&, class RDLNode*&) const;
        virtual void Update(f32);
        u16 get_style_id();
        void set_style_id(u16);

        virtual operator class StyleNode *();
        virtual operator class StyleNode const*() const;

        u16 styleFlag;
};

class IMPORT ParagraphNode : public RDLNode
{
    public:
        ParagraphNode(const ParagraphNode&);
        ParagraphNode();
        virtual ~ParagraphNode();
        class ParagraphNode& operator=(class ParagraphNode const&);
        virtual class RDLNode* Clone() const;
        virtual void Execute(class TextRenderContext&, bool);
        virtual void GetElementPos(int, class TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(class TextRenderContext const&, struct VisualSize&) const;
        virtual bool SplitAtSize(class TextRenderContext const&, int, u32, class RDLNode*&, class RDLNode*&) const;
        virtual void Update(f32);

        virtual operator class ParagraphNode *();
        virtual operator class ParagraphNode const*() const;
};

class IMPORT TextNode : public RDLNode
{
    public:
        TextNode(const TextNode&);
        TextNode(const st6::wstring&, int);
        TextNode(const u16*, int);
        TextNode();
        virtual ~TextNode();

        class TextNode& operator=(class TextNode const&);
        virtual class RDLNode* Clone() const;
        virtual void Execute(class TextRenderContext&, bool);
        virtual void GetElementPos(int, class TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(class TextRenderContext const&, struct VisualSize&) const;
        virtual bool SplitAtSize(class TextRenderContext const&, int, u32, class RDLNode*&, class RDLNode*&) const;
        virtual void Update(f32);
        void append_text(const st6::wstring&, int);
        void append_text(const u16*, int);
        const st6::wstring& get_text() const;
        void set_text(const st6::wstring&, int);
        void set_text(const u16*, int);

        operator TextNode*() override;
        operator const TextNode*() const override;

        st6::wstring text;
};

class IMPORT TextPtrNode : public RDLNode
{
    public:
        TextPtrNode(const TextPtrNode&);
        TextPtrNode(const u16*, int);
        TextPtrNode();
        virtual ~TextPtrNode();
        TextPtrNode& operator=(const TextPtrNode&);
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, u32, RDLNode*&, RDLNode*&) const;
        virtual void Update(f32);
        const u16* get_text() const;
        int get_text_length() const;
        void set_text(const u16*, int);

        virtual operator TextPtrNode*();
        virtual operator const TextPtrNode*() const;

        const wchar_t* text;
        int textLength;
};

class IMPORT JustifyNode : public RDLNode
{
    public:
        enum class TextJustify
        {
            Left,
            Centre,
            Right
        };

        JustifyNode(const JustifyNode&);
        JustifyNode(TextJustify);
        virtual ~JustifyNode();
        JustifyNode& operator=(const JustifyNode&);
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, u32, RDLNode*&, RDLNode*&) const;
        virtual void Update(f32);
        TextJustify get_justify();
        void set_justify(TextJustify);

        virtual operator JustifyNode*();
        virtual operator const JustifyNode*() const;

    public:
        TextJustify justify;
};

class IMPORT PositionNode : public RDLNode
{
    public:
        PositionNode(const PositionNode&);
        PositionNode();
        virtual ~PositionNode();
        PositionNode& operator=(const PositionNode&);
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, u32, RDLNode*&, RDLNode*&) const;
        virtual void Update(f32);

        f32 get_pos_h();
        f32 get_pos_v();
        bool is_rel_h();
        bool is_rel_v();
        void set_pos(f32, f32);
        void set_pos_h(f32);
        void set_pos_v(f32);
        void set_rel_h(bool);
        void set_rel_v(bool);

        virtual operator PositionNode*();
        virtual operator const PositionNode*() const;

        f32 x;
        f32 y;
        bool isRelX;
        bool isRelY;
};

class IMPORT AttribStackNode : public RDLNode
{
    public:
        enum class Op
        {
            Default = 3
        };

        AttribStackNode(const AttribStackNode&);
        AttribStackNode(Op);
        AttribStackNode();
        virtual ~AttribStackNode();
        AttribStackNode& operator=(const AttribStackNode&);
        virtual class RDLNode* Clone() const;
        virtual void Execute(class TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, struct VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, u32, RDLNode*&, RDLNode*&) const;
        virtual void Update(f32);
        Op get_operation();
        void set_operation(Op);

        virtual operator AttribStackNode*();
        virtual operator const AttribStackNode*() const;

        Op operation;
};

class IMPORT RDLReNode : public RDLNode
{
    public:
        RDLReNode(RenderDisplayList&);
        RDLReNode(const RDLReNode&);
        virtual ~RDLReNode();
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, u32, RDLNode*&, RDLNode*&) const;
        virtual void Update(f32);
        const RenderDisplayList& get_list();

        virtual operator RDLReNode*();
        virtual operator const RDLReNode*() const;
};

class IMPORT TRANode
{
    public:
        TRANode(const TextRenderAttributes&, u32, u32);
        TRANode(const TRANode&);
        TRANode();
        virtual ~TRANode();
        TRANode& operator=(const TRANode&);
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, u32, RDLNode*&, RDLNode*&) const;
        virtual void Update(f32);
        const TextRenderAttributes& get_attributes();
        u32 get_default_mask();
        u32 get_mask();
        void set_attributes(const TextRenderAttributes&, u32);
        void set_default_mask(u32);
        void set_mask(u32);

        virtual operator TRANode*();
        virtual operator const TRANode*() const;

        unsigned attributes;
        int mask;
        int defaultMask;
};

class IMPORT ImageNode
{
    public:
        ImageNode(const ImageNode&);
        ImageNode(const TextRenderContext::Image*);
        ImageNode();
        virtual ~ImageNode();
        ImageNode& operator=(const ImageNode&);
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, u32, RDLNode*&, RDLNode*&) const;
        virtual void Update(f32);
        const TextRenderContext::Image* get_image();
        void set_image(const TextRenderContext::Image*);

        virtual operator ImageNode*();
        virtual operator const ImageNode*() const;

        TextRenderContext::Image* image;
};

class IMPORT XMLReader
{
    public:
        XMLReader(const XMLReader&);
        XMLReader();
        XMLReader& operator=(const XMLReader&);
        virtual bool extract_text_from_buffer(u16*, u32, u32&, const char*, u32);
        virtual bool read_buffer(RenderDisplayList&, const char*, u32);
        virtual bool read_file(RenderDisplayList&, const char*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT XMLWriter
{
    public:
        XMLWriter(const XMLWriter&);
        XMLWriter();
        XMLWriter& operator=(const XMLWriter&);
        virtual bool write_buffer(const RenderDisplayList&, char*, u32, u32&);
        virtual bool write_file(const RenderDisplayList&, const char*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};
