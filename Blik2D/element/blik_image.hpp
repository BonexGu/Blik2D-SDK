﻿#pragma once
#include <element/blik_color.hpp>
#include <element/blik_rect.hpp>

namespace BLIK
{
    //! \brief 재질-이미지
    class Image
    {
    public:
        enum class Format {Null, Bmp, Jpg};

    public:
        Image();
        Image(const Image& rhs);
        ~Image();
        Image& operator=(const Image& rhs);

    public:
        Image& SetName(chars name);
        bool Save(chars pathname = "") const;
        bool Load(id_assetpath_read assetpath = nullptr);
        bool LoadBitmap(id_bitmap_read bitmap);
        bool LoadBitmapFromBits(bytes bits, sint32 width, sint32 height, sint32 bitcount, bool flip);
        bool LoadUIBitmap(id_bitmap_read bitmap);
        void Crear();
        id_bitmap CopiedBitmap(sint32 l = 0, sint32 t = 0, sint32 r = -1, sint32 b = -1) const;
        void ChangeToMagentaAlpha();
        void RestoreFromMagentaAlpha();
        void ReplaceAlphaChannelBy(id_bitmap_read src);

    public:
        inline bool HasBitmap() const {return (m_bitmap != nullptr);}
        inline id_bitmap_read GetBitmap() const {return m_bitmap;}
        inline id_image_read GetImage() const {return GetImageCore(Color(Color::ColoringDefault), GetImageWidth(), GetImageHeight());}
        inline id_image_read GetImage(const Color& coloring) const {return GetImageCore(coloring, GetImageWidth(), GetImageHeight());}
        inline id_image_read GetImage(const sint32 width, const sint32 height) const {return GetImageCore(Color(Color::ColoringDefault), width, height);}
        inline id_image_read GetImage(const Color& coloring, const sint32 width, const sint32 height) const {return GetImageCore(coloring, width, height);}
        inline void SetImageCacheMax(const sint32 count) {BLIK_ASSERT("count값은 1이상이어야 합니다", 1 <= count); m_image_cache_max = count;}
        sint32 GetImageWidth() const;
        sint32 GetImageHeight() const;
        inline sint32 GetWidth() const {return m_valid_rect.r - m_valid_rect.l;}
        inline sint32 GetHeight() const {return m_valid_rect.b - m_valid_rect.t;}
        inline sint32 L() const {return m_valid_rect.l;}
        inline sint32 T() const {return m_valid_rect.t;}
        inline sint32 R() const {return m_valid_rect.r;}
        inline sint32 B() const {return m_valid_rect.b;}
        inline bool HasChild() const {return (0 < m_child_ixzone.Count());}

    public:
        inline sint32 PatchXCount() const {return m_patch_xzone.Count();}
        inline sint32 PatchYCount() const {return m_patch_yzone.Count();}
        inline sint32 PatchX(sint32 i) const {return m_patch_xzone[i].x;}
        inline sint32 PatchXEnd(sint32 i) const {return m_patch_xzone[i].xend;}
        inline sint32 PatchY(sint32 i) const {return m_patch_yzone[i].y;}
        inline sint32 PatchYEnd(sint32 i) const {return m_patch_yzone[i].yend;}
        inline sint32 PatchL() const {return m_patch_xzone[0].x;}
        inline sint32 PatchT() const {return m_patch_yzone[0].y;}
        inline sint32 PatchR() const {return m_patch_xzone[-1].xend;}
        inline sint32 PatchB() const {return m_patch_yzone[-1].yend;}
        inline sint32 PatchSumWidth() const {return m_patch_calced_sum_width;}
        inline sint32 PatchSumHeight() const {return m_patch_calced_sum_height;}
        inline sint32 PatchSrcXCount() const {return m_patch_calced_src_x.Count();}
        inline sint32 PatchSrcYCount() const {return m_patch_calced_src_y.Count();}
        inline const sint32* PatchSrcXArray() const {return &m_patch_calced_src_x[0];}
        inline const sint32* PatchSrcYArray() const {return &m_patch_calced_src_y[0];}
        inline const sint32* PatchDstXArray() const {return &m_patch_cached_dst_x[0];}
        inline const sint32* PatchDstYArray() const {return &m_patch_cached_dst_y[0];}

    public:
        Rect CalcChildRect(const Rect& guide, sint32 ix, sint32 iy, sint32 xcount, sint32 ycount) const;
        bool UpdatePatchBy(float w, float h) const;

    private:
        void ResetBitmap();
        void ResetData();
        void MakeData(sint32 l, sint32 t, sint32 r, sint32 b);
        void RecalcData();
        id_image_read GetImageCore(const Color& coloring, sint32 width, sint32 height) const;

    private:
        String m_filepath;
        Format m_fileformat;
        id_bitmap m_bitmap;
        sint32 m_image_cache_max;
        typedef Map<id_image> ImageMap;
        mutable Map<ImageMap> m_image_cached_map;
        typedef struct {uint32 coloring; uint64 sizing;} CacheKeys;
        mutable Queue<CacheKeys*> m_image_cached_queue;
        rect128 m_valid_rect;
        Array<ixzone64, datatype_pod_canmemcpy> m_child_ixzone;
        Array<iyzone64, datatype_pod_canmemcpy> m_child_iyzone;
        Array<xzone64, datatype_pod_canmemcpy> m_patch_xzone;
        Array<yzone64, datatype_pod_canmemcpy> m_patch_yzone;
        sint32 m_patch_calced_sum_width;
        sint32 m_patch_calced_sum_height;
        sint32s m_patch_calced_src_x;
        sint32s m_patch_calced_src_y;
        mutable float m_patch_cached_dst_terms_w;
        mutable float m_patch_cached_dst_terms_h;
        mutable bool m_patch_cached_dst_visible_w;
        mutable bool m_patch_cached_dst_visible_h;
        mutable sint32s m_patch_cached_dst_x;
        mutable sint32s m_patch_cached_dst_y;
    };
}
