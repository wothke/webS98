downloaded from: http://www.vesta.dti.ne.jp/~tsato/soft_s98v3.html
------------------------------------------------------------------

m_s98.kpi S98V3�Ή���

�����?
  KbMediaPlayer��S98���̑����X�v���O�C����S98V3�ɑΉ����������ł��B
  ���XS98V3��m_s98�������ŗ��p���Ă���S98V2���g���������ł��B

this is?
?? S98 of KbMediaPlayer and others Various plug-ins correspond to S98V3.
?? Originally S98V3 is an extension of S98V2 which m_s98 used internally.
  
  
���C�Z���X
  �I���W�i���ɏ]���܂��B

license
?? I will follow the original.

���m�̕s�

 *�^�O�t��S98V3�t�@�C����KBM�{�̂ł��܂��Đ��ł��Ȃ��B
  KBM�{�̂�S98V1�Ǝv������ŏ��擾�Ɏ��s����l�ł��B
  �����Ƃ��Ĉ�U�𓀂��ĉ��t���Ă��������B
  �����Ή���KBM�{�̂��Ώ����Ȃ��Ɩ����ł��B(�{�̂̍X�V���ŋߖ����̂Ŗ]�ݔ��ł�����)
  
Known bug

? * The tagged S98V3 file can not be played well on the KBM itself.
?? It seems that KBM main body is S98V1 and fails to acquire information.
?? Please unzip once and play as a workaround.
?? It is impossible for KBM main body to deal with formal correspondence. (It is thin as you are not updating the main body so recently)
  
 *VGZ�̃��[�h�x��
  gz��->s98�ϊ�->�Đ���3�i�K�𓥂�Ń��[�h����̂�native�v���C���[���
  ���t�J�n���x���ł��B
  KBM�{�̂��ʓrgz��->�^�O�ǂݍ��݂����s����̂ł���ɒx���Ȃ�͗l�B(������)

* Loading VGZ slow
?? From the native player to load it by following three steps of decompressing gz -> s 98 conversion -> playback
?? The performance start is late.
?? It seems that the KBM itself will be delayed further since gz decompression -> tag reading is executed separately. (Unverified)
  
�O�񂩂�̕ύX�_

 *S98&VGM:�Đ��f�o�C�X�̎��g���w����I�[�gor44100KHz�ȊO�Ɏw�肵���ꍇ�A
          OPLL�̍Đ����x�����������s����C��(�I���W�i������̐��݃o�O)
 *S98:OPL3�̍Đ��ŗ�����s����C���B

Changes since last time

? * S98 & VGM: When specifying the frequency specification of the playback device to other than Auto or 44100 KHz,
?????????? Fixed wrong bug in OPLL's playback speed (potential bug from original)
? * S98: Fixed a bug that dropped on OPL3 playback.


�I���W�i������̕ύX�_

 *S98:S98V3�ɑΉ�
 *VGM:GameGear�̃p�����C�����܂����B
 *VGM:OPN2-PCM�̕s��C�����܂����B
 *VGM:v1.50�d�l�̒ǉ��R�}���h�ɑΉ��B
 *X1F:PSG�̍Đ����g�����C�����܂����B
 *zlib���X�V���܂����B
  zlib 1.2.3 (c) 1995-2005 Jean-loup Gailly and Mark Adler

Changes from the original

? * S98: Corresponds to S98V3
? * VGM: We fixed bread of GameGear.
? * VGM: A bug in OPN2 - PCM was fixed.
? * VGM: Corresponds to additional command of v1.50 specification.
? * X1F: PSG playback frequency was corrected.
? * Updated zlib.
?? zlib 1.2.3 (c) 1995-2005 Jean-loup Gailly and Mark Adler
