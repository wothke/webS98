------------------------------------------------------------------------------
        FM Sound Generator with OPN/OPM interface
        Copyright (C) by cisc 1998, 2003.
------------------------------------------------------------------------------

�y�T�v�z
	C++ �ɂ�� FM/PSG �����̎����ł��B
	
	AY8910, YM2203, YM2151, YM2608, YM2610 �����̃C���^�[�t�F�[�X��
	�������Ă���܂��B

�yOverview�z
It is an implementation of FM / PSG sound source by C ++.
In case
Interfaces equivalent to AY 8910, YM 2203, YM 2151, YM 2608, and YM 2610

�y�g�����z
	(TODO:���g������)

�yHow to use�z
(TODO: write the contents)
	
�y���Ӂz
	�ȑO�̃o�[�W�������������������܂����B�C���^�[�t�F�[�X��
	�������Ă��Ȃ�����ł����A��������̃o�O���B��Ă��邩������܂���B

	YM2610 �͓���`�F�b�N���炵�Ă��܂���B

	���`�⊮���[�h(interpolation)�͔p�~����܂����B
	Init() �̈����d�l�͕ς���Ă��܂��񂪁Ainterpolation = true �ɂ��Ă�
	����͕ς��܂���B

	OPNA::Init/SetRate �ŗ^����`�b�v�N���b�N�̒l�̎d�l��
	�ȑO�� M88 �ɓ��ڂ���Ă����o�[�W�����ƈقȂ��Ă��܂��D

�yCaution�z
I made some changes from the previous version. The interface is
I do not intend to fuse, but some bugs may be hiding.

YM 2610 does not even check the operation.

Linear interpolation mode (interpolation) has been deprecated.
The argument specification of Init () has not changed, but even if interpolation = true
The behavior does not change.

Specification of chip clock value given by OPNA :: Init / SetRate is
It is different from the version installed in the previous M88.

�y���쌠�A�ƐӋK��z

	�E�{�\�[�X�R�[�h�͍��(cisc@retropc.net) �����쌠�����L���Ă��܂��B
	
	�E�{�\�[�X�R�[�h�͂��邪�܂܂ɒ񋟂������̂ł���C
	  �Öًy�і����I�ȕۏ؂���؊܂݂܂���D
	  
	�E�{�\�[�X�R�[�h�𗘗p�������ƁC���p���Ȃ��������ƁC
	  ���p�ł��Ȃ��������ƂɊւ��Đ��������邢�͐�����Ɨ\�������
	  ���Q�ɂ��āC��҂͈�ؐӔC�𕉂��܂���D
	  
	�E�{�\�[�X�R�[�h�́C�ȉ��̐����𖞂������莩�R�ɉ��ρE�g�ݍ��݁E
	  �z�z�E���p���邱�Ƃ��ł��܂��D
	  
	  1. �{�\�t�g�̗R��(���, ���쌠)�𖾋L���邱��.
	  2. �z�z����ۂɂ̓t���[�\�t�g�Ƃ��邱�ƁD
	  3. ���ς����\�[�X�R�[�h��z�z����ۂ͉��ϓ��e�𖾎����邱��.
	  4. �\�[�X�R�[�h��z�z����ۂɂ͂��̃e�L�X�g����؉��ς�����
	     ���̂܂ܓY�t���邱�ƁD
	  
	�E���J�̍ۂɍ�҂ւ̘A���𒸂���΍K���ł��D
	
	�E���p�\�t�g(�V�F�A�E�F�A�܂�) �ɖ{�\�[�X�R�[�h�̈ꕔ�C�܂���
	  �S����g�ݍ��ލۂɂ́C���O�ɍ�҂̍��ӂ𓾂�K�v������܂��D

	  
�yCopyright, Disclaimer�z

�E This source code is copyrighted by the author (cisc@retropc.net).
In case
�E This source code is provided as it is,
No implied or explicit warranty is included.
In case
�E I used this source code, did not use it,
It is expected to arise or to occur with respect to what was not available
The author is not responsible for any damage.
In case
�E This source code can be freely modified / incorporated as long as it satisfies the following restrictions
It can be distributed and used.
In case
1. Specify the origin (author, copyright) of this software.
2. To distribute it should be free software.
3. When distributing the modified source code, indicate the contents of modification.
4. When distributing the source code, without modifying this text at all
Attach as it is.
In case
�E I am pleased if you can contact the author when publishing.
In case
�E Part of this source code on commercial software (including shareware) or
When incorporating all, it is necessary to obtain agreement of the author beforehand.	  

�y�ύX�_�z
008	030902	�E�o�̓T���v�����O���[�g�̐ݒ���A�`�b�v�����̍����T���v
                  �����O���[�g�ƈقȂ�ݒ�ɂ���ƃG���x���[�v����������
                  �Ȃ�����C���B

007a	030608	�E�̈�O�A�N�Z�X���������̂��C�� (Thanks to �o�h�D�l)

007	030607	�E�Č����̌���
		�EOPN: SSG-EG �̃T�|�[�g
		�E���`�⊮�̔p�~
		�Easm �ł̔p�~
		�E�}���`�X���b�h�t���[�ɂȂ����H

006	010330	�E�Č����Ɋւ��Ă����炩�蒼��(�����g�C�o�̓^�C�~���O��)

005	010317	�EOPN: FM �����̍������g�����o�͎��g�������Ⴂ�Ƃ��ɁC
		  �⊮���g���Ɖ��s�ɂȂ�/�����܂Ƃ��ɏo�Ȃ��Ȃ�����C��.
		�EFM: �⊮���g��Ȃ����̐��x���グ�Ă݂�D
		  ��肪�N������ fmgeninl.h �� FM_RATIOBITS �� 8 �ɖ߂��Ƌg�D

004a	010311	�EOPM: �m�C�Y���������������郌�x��(�H)�܂ŏC��.
		�EOPNA/OPM: FM_USE_CALC2 �p�~.
		�E�f�O���C��, �Ȃ�̂��߂� cvs �ŊǗ����Ă���񂾂��c(T-T
		  OPNB: ADPCMB ROM �}�X�N�쐬�~�X.
		  OPNB: ADPCMA �X�e�[�^�X�t���O�֌W�̋����C��.
		  OPM: LFO �p�����[�^�̏�������Y��Ă����̂��C��.

003	010124	�EOPNA/OPM�F ���ۂɂ͕⊮�O�̒l���o�͂��Ă����o�O���C��.

002	010123	�E�������g�����o�͎��g�����Ⴂ�Ƃ��ł���Ԃ������悤�ɂ���.
		�EOPN: ��Ԏ��Ƀv���X�P�[���̐ݒ��ύX�����Ƃ��ɉ���������
		  �o�O���C��.
		�EOPNA/B: LFO �������Ȃ��o�O���C��.

001 	000928	�E�����o�[�W����

�ychange point�z
008 030902 �E Set the output sampling rate to the original synthesis sample of chip
?????????????????? If it is set differently from the ring rate, the envelope is amusing
?????????????????? Fixed the problem becoming.

007a 030608 �E Corrected out of area access (Thanks to PI.)

007 030607 �E Improve reproducibility
�E OPN: Support for SSG-EG
�E Elimination of linear interpolation
�E Abolition of asm version
�E Have you become multithread free?		

006 010330 �E Some rework about reproducibility (sine wave, output timing etc.)

005 010317 OPN: When the synthesized frequency of the FM sound source is lower than the output frequency,
Fixed a problem that when you use completion, you get tone / the sound does not go out correctly.
�E FM: Try increasing accuracy when not using completion.
When problems occur, return FM_RATIOBITS in fmgeninl.h to 8.

004a 010311 �E OPM: Fixed the level to which you can hear the noise so much (?).
�E OPNA / OPM: FM_USE_CALC 2 obsolete.
�E Degre corrected, what is managed by cvs for what ... (T - T
OPNB: ADPCMB ROM mask mistake.
OPNB: Behavior restoration related to ADPCMA status flag.
OPM: Fixed forgetting to initialize LFO parameters.

003 010124 �E OPNA / OPM: Fixed a bug that actually output values ??before completion.

002 01012 �E Make interpolation work even when the synthesized frequency is lower than the output frequency.
�E OPN: Sounds unnatural when prescaler setting is changed during interpolation
Fixed a bug.
�E OPNA / B: Fixed a bug that LFO does not work.

001 000928 �E Initial version		

$Id: readme.txt,v 1.1 2003/06/07 08:25:20 cisc Exp $
