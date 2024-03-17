#pragma once


class IMPORT XMLReader
{
    public:
    XMLReader(const XMLReader&);
    XMLReader();
    XMLReader& operator=(const XMLReader&);
    virtual bool extract_text_from_buffer(unsigned short*, unsigned int, unsigned int&, const char*, unsigned int);
    virtual bool read_buffer(RenderDisplayList&, const char*, unsigned int);
    virtual bool read_file(RenderDisplayList&, const char*);

    public:
    unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT XMLWriter
{
    public:
    XMLWriter(const XMLWriter&);
    XMLWriter();
    XMLWriter& operator=(const XMLWriter&);
    virtual bool write_buffer(const RenderDisplayList&, char*, unsigned int, unsigned int&);
    virtual bool write_file(const RenderDisplayList&, const char*);

    public:
    unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT NullNode
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
        virtual bool SplitAtSize(const TextRenderContext&, int, unsigned int, RDLNode*&, RDLNode*&) const;
        virtual void Update(float);

        virtual operator NullNode*();
        virtual operator const NullNode*() const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT StyleNode
{
    public:
        StyleNode(const StyleNode&);
        StyleNode(unsigned short);
        StyleNode();
        /*virtual ~StyleNode();
        class StyleNode & operator=(class StyleNode const &);
        virtual class RDLNode * Clone()const ;
        virtual void Execute(class TextRenderContext &,bool);
        virtual void GetElementPos(int,class TextRenderContext &,int &)const ;
        virtual void GetElementSize(int &)const ;
        virtual void GetVisualSize(class TextRenderContext const &,struct VisualSize &)const ;
        virtual bool SplitAtSize(class TextRenderContext const &,int,unsigned int,class RDLNode * &,class RDLNode * &)const ;
        virtual void Update(float);
        unsigned short get_style_id();
        void set_style_id(unsigned short);

        virtual operator class StyleNode *();
        virtual operator class StyleNode const *()const ;*/

    public:
        unsigned char data[1024];
};

class IMPORT ParagraphNode
{
    public:
        ParagraphNode(const ParagraphNode&);
        ParagraphNode();
        /*virtual ~ParagraphNode();
        class ParagraphNode & operator=(class ParagraphNode const &);
        virtual class RDLNode * Clone()const ;
        virtual void Execute(class TextRenderContext &,bool);
        virtual void GetElementPos(int,class TextRenderContext &,int &)const ;
        virtual void GetElementSize(int &)const ;
        virtual void GetVisualSize(class TextRenderContext const &,struct VisualSize &)const ;
        virtual bool SplitAtSize(class TextRenderContext const &,int,unsigned int,class RDLNode * &,class RDLNode * &)const ;
        virtual void Update(float);

        virtual operator class ParagraphNode *();
        virtual operator class ParagraphNode const *()const ;*/
};

class IMPORT TextNode
{
        char Buf[1024];

    public:
        TextNode(const TextNode&);
        TextNode(const st6::wstring&, int);
        TextNode(const unsigned short*, int);
        TextNode();
        /*virtual ~TextNode();
        class TextNode & operator=(class TextNode const &);
        virtual class RDLNode * Clone()const ;
        virtual void Execute(class TextRenderContext &,bool);
        virtual void GetElementPos(int,class TextRenderContext &,int &)const ;
        virtual void GetElementSize(int &)const ;
        virtual void GetVisualSize(class TextRenderContext const &,struct VisualSize &)const ;
        virtual bool SplitAtSize(class TextRenderContext const &,int,unsigned int,class RDLNode * &,class RDLNode * &)const ;
        virtual void Update(float);
        void append_text(st6::wstring const &,int);
        void append_text(unsigned short const *,int);
        st6::wstring const & get_text()const ;
        void set_text(st6::wstring const &,int);
        void set_text(unsigned short const *,int);

        virtual operator class TextNode *();
        virtual operator class TextNode const *()const ;*/
};

class IMPORT TextPtrNode
{
    public:
        TextPtrNode(const TextPtrNode&);
        TextPtrNode(const unsigned short*, int);
        TextPtrNode();
        virtual ~TextPtrNode();
        TextPtrNode& operator=(const TextPtrNode&);
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, unsigned int, RDLNode*&, RDLNode*&) const;
        virtual void Update(float);
        const unsigned short* get_text() const;
        int get_text_length() const;
        void set_text(const unsigned short*, int);

        virtual operator TextPtrNode*();
        virtual operator const TextPtrNode*() const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT JustifyNode
{
    public:
        JustifyNode(const JustifyNode&);
        JustifyNode(enum TextJustify);
        virtual ~JustifyNode();
        JustifyNode& operator=(const JustifyNode&);
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, unsigned int, RDLNode*&, RDLNode*&) const;
        virtual void Update(float);
        TextJustify get_justify();
        void set_justify(TextJustify);

        virtual operator JustifyNode*();
        virtual operator const JustifyNode*() const;

    public:
        unsigned char data[1024];
};

class IMPORT PositionNode
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
        virtual bool SplitAtSize(const TextRenderContext&, int, unsigned int, RDLNode*&, RDLNode*&) const;
        virtual void Update(float);
        float get_pos_h();
        float get_pos_v();
        bool is_rel_h();
        bool is_rel_v();
        void set_pos(float, float);
        void set_pos_h(float);
        void set_pos_v(float);
        void set_rel_h(bool);
        void set_rel_v(bool);

        virtual operator PositionNode*();
        virtual operator const PositionNode*() const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

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

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT RDLReNode
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
        virtual bool SplitAtSize(const TextRenderContext&, int, unsigned int, RDLNode*&, RDLNode*&) const;
        virtual void Update(float);
        const RenderDisplayList& get_list();

        virtual operator RDLReNode*();
        virtual operator const RDLReNode*() const;

    public:
        unsigned char data[1024];
};